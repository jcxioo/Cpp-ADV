 ///
 /// @file    DictProducer.cpp
 /// @author  jcx(yxjcxstack@gmail.com)
 /// @date    2018-05-13 23:49:24
 ///
 
#include "Mylogger.h"
#include "DictProducer.h"
#include "config.h"

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <ctype.h>
#include <algorithm>
#include <locale>
#include <cstring>
#include <iterator>

using std::cout;
using std::endl;
using std::map;
using std::vector;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::istringstream;

using namespace wd;
DictProducer::DictProducer(const string & dir)
: _dir(dir)
{
	LogInfo("debug DictProducer()"); 
}

//	DictProducer(const string & dir, SplitTool * splitTool);

void DictProducer::build_dict()
{
	Configuration configuration("/home/jcx/cppgit/Project1/conf/my.conf");
	ifstream ifs("/home/jcx/cppgit/Project1/data/english.txt");
	if(!ifs)
	{
		LogError("build_dict ifs open error!");
		return ;
	}
	string line;
	while(getline(ifs, line))
	{	
		line.erase(	
			 remove_if(line.begin(),
					   line.end(),
					   static_cast<int(*)(int)>(&ispunct)),
			 line.end());//去除标点
		line.erase(	
			 remove_if(line.begin(),
					   line.end(),
					   static_cast<int(*)(int)>(&isdigit)),
			 line.end());//去除数字
		for(size_t idx = 0; idx != line.size(); ++idx)
		{
			line[idx] = tolower(line[idx]);
		}
		istringstream iss(line);
		string word;
		while(iss >> word)
		{
			++ _dict[word];
		}
	}
		ifs.close();
		return;
}

void DictProducer::build_index()
{
//	unordered_map<string, set<int>> hastbale;
	size_t number = 0;
	for(map<string,int>::iterator it = _dict.begin(); it != _dict.end(); ++it)
	{
		++number;
		string tmp;
	   for(size_t idx = 0; idx != it->first.size(); ++idx)
	   {
			tmp = it->first[idx];
			_hastbale[tmp].insert(number);
		//	LogInfo(tmp);
	//		hastbale.insert(std::make_pair(it->first[idx],number));
	   }
	}
	return ;
		
}

void DictProducer::build_cn_dict()
{}


void DictProducer::store_dict(const char * filepath)
{
	ofstream ofs(filepath);
	if(!ofs)
	{
		LogError("store_dict ofstream open error!");
		return;
	}
	for(auto & record : _dict)
	{
		ofs << record.first << " " << record.second << "\n";
	}
	ofs.close();	
}


void DictProducer::store_index(const char * filepath)
{
	ofstream ofs(filepath);
	if(!ofs)
	{
		LogError("store_index ofstream open error!");
		return;
	}	
	  for (auto & alp : _hastbale)
	   {
	       string tmp = alp.first;
		   ofs << alp.first<< "\n" ;
		   for (set<int>::iterator it = _hastbale[tmp].begin(); it != _hastbale[tmp].end(); ++it)
			{
				ofs << *it << " " ;
			}
		   ofs << endl;
		   LogInfo(alp.first);
	   }
}

void DictProducer::show_files()const
{}

void DictProducer::show_dict()const 
{}

