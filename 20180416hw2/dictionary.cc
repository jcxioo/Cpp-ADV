///
/// @file    dictionary.cc
/// @author  jcx(yxjcxstack@gmail.com)
/// @date    2018-04-13 08:14:46
///

#include <string.h>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::istringstream;
struct Record
{
	Record(const string & word, int freq)
	: _word(word)
	, _freq(freq)
	{}
	string _word;
	int _freq;
};
bool operator<(const Record & lhs, const Record & rhs)
{
	return lhs._word < rhs._word;
}

class Dictionary
{
	public:
		Dictionary()
		{
			_dict.reserve(1000);//为Vec申请空间
			cout << "Dictionary()" << endl;
		}

		void read(const string & filename)
		{
			ifstream ifs(filename);
			if(!ifs)
			{
				cout << "ifstream open error!" << endl;
				return;
			}
			string line;
			int count = 0;
			while(getline(ifs, line))
			{
				istringstream iss(line);
			 	string word;
				while(iss >> word)
				{
					//循环读取单词，会判断空格
					if(isWord(word))
						processWord(word);			
				}
				++count;
				if((count % 100) == 0)//每100行打印一次
				{
					cout << "count = " << count << endl;
				}
			}
			ifs.close();
			std::sort(_dict.begin(),_dict.end());//排序
		}
		void store(const string & filename)
		{
				ofstream ofs(filename);
				if(!ofs){
					cout << "ofstream open error!" << endl;
					return;
				}
				for (auto & record : _dict)
				{
					ofs << record._word << " " << record._freq << "\n";
				}
				ofs.close();
		}
	private:
		bool isWord(const string & word)
		{
			for(size_t idx = 0; idx != word.size(); ++idx)
			{
				if(isdigit(word[idx]))
					return false;
			}
			return true;
		}

		void processWord(const string & word)
		{
			size_t idx;
			for(idx = 0; idx != _dict.size(); ++idx)
			{
				if(_dict[idx]._word ==  word)
				{
					++_dict[idx]._freq;
					break;
				}
			}
			if(idx >= _dict.size())
			{
				_dict.push_back(Record(word,1));
			}
		}
	private:
		vector<Record> _dict;
};



int main(void)
{
	Dictionary dictionary;
	string filename("/home/jcxioo/cppgit/20180416hw2/The_Holy_Bible.txt");
	dictionary.read(filename);
	//dictionary.read("The_Holy_Bible.txt");
	dictionary.store("dic.txt");

	return 0;
}
