
#include "TcpServer.h"
#include "Threadpool.h"
#include "Mylogger.h"
#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstring>

using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::pair;
using std::set;
using std::string;
using std::ifstream;
using std::fstream;
using std::istringstream;

using namespace std;
struct MyResult
{
	string _word;//被查单词
	int _iFreq;//词频
	int _iDist;//距离
};


class Cache{
	private:
		std::unordered_map<string, string> _hashMap;

};
class Mydict
{
	class AutoRelease
	{
		public:
			AutoRelease(){LogInfo("AutoRelease()");}
			~AutoRelease(){
				if(_pInstance)
				{
					delete _pInstance;
					LogInfo("~AutoRelease()");
				}
			}
	};
	public:
	static Mydict * createInstance()
	{
		if(NULL == _pInstance)	
		{
			_pInstance = new Mydict;
		}
		return _pInstance;
	}
	void init(const char * dictEnPath, const char * dictEnIndexPath, 
			const char * dictCnPath,const char * dictCnIndexPath) 
	{
		ifstream dictEnIfs(dictEnPath);
		ifstream dictEnIndexIfs(dictEnIndexPath);
		ifstream dictCnIfs(dictCnPath);
		ifstream dictCnIndexIfs(dictCnIndexPath);
		LogInfo(dictEnPath);
		LogInfo(dictCnPath);
		if(!dictEnIfs)
		{
			LogError("dictEn ifstream open error!");
			//	return;
		}
		if(!dictCnIfs)
		{
			LogError("dictCn ifstream open error!");
			//	return;
		}
		char tmp[1000];
		while(dictEnIfs.getline(tmp,1000))	
		{
			string line(tmp);
			size_t pos = line.find(' ');
			if(pos == string::npos) return;
			string word = line.substr(0,pos);
			int num = stoi(line.substr(pos + 1));
			_dict.push_back(std::make_pair(word, num));
		}
		string line1;
		string line2;
		int set_num;
		while(getline(dictEnIndexIfs,line1),getline(dictEnIndexIfs,line2))
		{
	//		cout << line1 << endl;
	//		cout << line2 << endl;
			istringstream iss(line2);
			//		string word;
			while(	iss >> set_num)
			{
				_index_table[line1].insert(set_num);	
			}
		}
	}
	vector<pair<string, int>> & getDict()
	{
		return _dict;
	}
	map<string, set<int>> & getIndexTable()
	{
		return _index_table;
	}
	private:
	Mydict()
	{
		LogInfo("Mydict()");
	}
	~Mydict() {LogInfo("~Mydict()");}
	static Mydict * _pInstance;
	static AutoRelease _auto;
	vector<pair<string, int>> _dict;
	map<string, set<int> > _index_table;
};

Mydict * Mydict::_pInstance = createInstance();
Mydict::AutoRelease Mydict::_auto;

auto MyCompare = [](const MyResult & lhs, const MyResult & rhs)
{
//	return lhs._iDist > rhs._iDist;
	if( lhs._iDist > rhs._iDist)
	{	return  true; 	}
	else if(lhs._iDist < rhs._iDist)
	{   return  false;  }
	else{
		if(lhs._iFreq < rhs._iFreq)
		{ return true;}
		else if(lhs._iFreq > rhs._iFreq)
		{ return false;}
		else// if(lhs._iFreq == rhs._iFreq)
		{
			if(lhs._word > rhs._word)
			{
				return true;
			}
			return false;
		}
	}
	return true;
};
class Task
{
	public:
		Task(const string & query, 
				const wd::TcpConnectionPtr & conn)
			//	 std::priority_queue<MyResult, vector<MyResult>, decltype(MyCompare) > & resultQue)
			: _query(query)
			  , _conn(conn)
			  ,_resultQue(MyCompare)
	{
			_query.erase(_query.size()-1);

	}
		//process的执行是在一个计算线程里面完成的
		void process()
		{
			struct MyResult myresult;
			set<int> iset;
			Mydict * mydict = Mydict::createInstance();
			const char * dictEnPath = "/home/jcx/cppgit/Project1/data/mydict.dat";
			const char * dictEnIndexPath = "/home/jcx/cppgit/Project1/data/myindex.dat";
			const char * dictCnPath = " ";
			const char * dictCnIndexPath = " ";
			mydict->init(dictEnPath, dictEnIndexPath, 
					dictCnPath,dictCnIndexPath); 
			LogInfo("Task is processing.");
			queryIndexTable(myresult,mydict);
			LogInfo(myresult._word);
			//_conn->send(_queury);//如果直接去使用send，在计算线程里面完成了数据发送,不可取
			string ass_line;
			string tmp ;
			for(size_t idx = 0; idx != 10; ++idx)
			{
		//		cout << _resultQue.size() << endl ;
				if(tmp == _resultQue.top()._word)
				{
					_resultQue.pop();
					continue;
				}
				tmp = _resultQue.top()._word;
				//ass_line = ass_line +" " + tmp + std::to_string (_resultQue.top()._iDist) ;
				ass_line = ass_line +" " + tmp;
				
				_resultQue.pop();
			}
			//	string ass_line = _resultQue._word[0] +_resultQue._word[1] ;
			_conn->sendInLoop(ass_line);
			LogDebug("test3");

		}

	private:
		//   static bool MyCompare(const MyResult & lhs, const MyResult & rhs)
		//	{
		//		if( lhs._iDist < rhs._iDist)
		//		{}
		//	}
		void queryIndexTable(MyResult & myresult,Mydict * mydict)
		{
			//Mydict * mydict = Mydict::createInstance();
			cout << "queryIndexTable() " << endl;
		//	cout << _query << endl;
			//cout << mydict->getIndexTable().size() << endl;
			string alp ;
			for(size_t i = 0 ; i != _query.size(); ++i)
			{
				alp = _query[i];
				statistic(mydict->getIndexTable()[alp],  mydict, myresult);
			}
		}
		void statistic(set<int> & iset, Mydict * mydict,MyResult & myresult)
		{
			cout << "statistic() " << endl;
			for(auto it = iset.begin(); it != iset.end(); ++it)
			{
				myresult._word = mydict->getDict()[*it].first;
				//	LogDebug(myresult._word);
				myresult._iDist  = distance(mydict->getDict()[*it].first, _query);//pair.string
				//	cout << mydict->getDict()[*it].first << myresult._iDist << endl;
				//cout << mydict->getDict()[*it].first.size() <<"----" << _query.size()<<endl;
				myresult._iFreq = mydict->getDict()[*it].second;
				_resultQue.push(myresult);	
			}
		}

		int distance(const string & x, const string & y){

			int xlen = x.length();
			int ylen = y.length();
			int edit[3][30 + 1];
			memset(edit, 0, sizeof(edit));
			int i = 0;
			int j = 0;
			for (j = 0; j <= ylen; j++){
				edit[0][j] = j;
			}
			for (i = 1; i <= xlen; i++){
				edit[i % 3][0] = edit[(i - 1) % 3][0] + 1;
				for (j = 1; j <= ylen; j++){
					if (x[i - 1] == y[j - 1]) {
						edit[i % 3][j] = min(min(edit[i % 3][j - 1] + 1, edit[(i - 1) % 3][j] + 1),
								edit[(i - 1) % 3][j - 1]);
					}
					else {
						if (i >= 2 && j >= 2 && x[i - 2] == y[j - 1] && x[i - 1] == y[j - 2]){
							edit[i % 3][j] = min(min(edit[i % 3][j - 1] + 1, edit[(i - 1) % 3][j] + 1),
									min(edit[(i - 1) % 3][j - 1] + 1, edit[(i - 2) % 3][j - 2] + 1));
						}
						else {
							edit[i % 3][j] = min(min(edit[i % 3][j - 1] + 1, edit[(i - 1) % 3][j] + 1),
									edit[(i - 1) % 3][j - 1] + 1);
						}
					}
				}
			}
			return edit[(i - 1) % 3][j - 1];
		}


//			int distance(const string & str1, const string & str2)
//			{
//				int max1 = str1.size();
//				int max2 = str2.size();
//	
//				int **ptr = new int*[max1 + 1]();
//				for (int i = 0; i < max1 + 1; i++)
//				{
//					ptr[i] = new int[max2 + 1];
//				}
//	
//				for (int i = 0; i < max1 + 1; i++)
//				{
//					ptr[i][0] = i;
//				}
//	
//				for (int i = 0; i < max2 + 1; i++)
//				{
//					ptr[0][i] = i;
//				}
//	
//				for (int i = 1; i < max1 + 1; i++)
//				{
//					for (int j = 1; j< max2 + 1; j++)
//					{
//						int d;
//						int temp = min(ptr[i - 1][j] + 1, ptr[i][j - 1] + 1);
//						if (str1[i - 1] == str2[j - 1])
//						{
//							d = 0;
//						}
//						else
//						{
//							d = 1;
//						}
//						ptr[i][j] = min(temp, ptr[i - 1][j - 1] + d);
//					}
//				}
//				for (int i = 0; i < max1 + 1; i++)
//				{
//					for (int j = 0; j< max2 + 1; j++)
//					{
//						cout << ptr[i][j] << " ";
//					}
//					cout << endl;
//				}
//				int dis = ptr[max1][max2];
//	
//				for (int i = 0; i < max1 + 1; i++)
//				{
//					delete[] ptr[i];
//					ptr[i] = NULL;
//				}
//	
//				delete[] ptr;
//				ptr = NULL;
//	
//				return dis;
//			}
		//	void response(Cashe & cache);

	private:
		string _query;
		wd::TcpConnectionPtr _conn;
		std::priority_queue<MyResult, vector<MyResult>, decltype(MyCompare)>  _resultQue;

};
//std::Task::bool MyCompare;  
wd::Threadpool * g_threadpool = NULL;

void onConnection(const wd::TcpConnectionPtr &conn)
{
	cout << conn->toString() << endl;
	conn->send("hello, welcome to Chat Server.\r\n");
}

//运行在IO线程
void onMessage(const wd::TcpConnectionPtr &conn)
{
	std::string s(conn->receive());
	//	std::priority_queue<MyResult, vector<MyResult>, decltype(MyCompare) >  resultQue;
	//	Task task(s, conn, resultQue);
	Task task(s, conn);
	g_threadpool->addTask(std::bind(&Task::process, task));
	cout << "> add task to threadpool" << endl;
}

void onClose(const wd::TcpConnectionPtr &conn)
{
	printf("%s close\n", conn->toString().c_str());
}

//class EchoServer
//{
//public:
//	void start();
//	void onMessage();
//	void onConnection();
//	void onClose();
//private:
//	Threadpool _threadpool;
//	TcpServer _server;
//};

int main(int argc, char const *argv[])
{
	wd::Threadpool threadpool(4, 10);
	g_threadpool = &threadpool;
	threadpool.start();

	wd::TcpServer tcpserver("192.168.110.129", 6666);
	tcpserver.setConnectionCallback(&onConnection);
	tcpserver.setMessageCallback(&onMessage);
	tcpserver.setCloseCallback(&onClose);

	tcpserver.start();

	return 0;
}
