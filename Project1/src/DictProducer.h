 ///
 /// @file    DictProducer.cpp
 /// @author  jcx(yxjcxstack@gmail.com)
 /// @date    2018-05-13 23:49:24
 ///

#ifndef __DICTPRODUCER_H__
#define __DICTPRODUCER_H__
#include "Mylogger.h"

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>

using std::cout;
using std::endl;
using std::map;
using std::vector;
using std::unordered_map;
using std::set;


namespace wd{
class DictProducer
{

	public:
		DictProducer(const string & dir);
//		DictProducer(const string & dir, SplitTool * splitTool);
		void build_dict();
		void build_cn_dict();
		void build_index();
		void store_dict(const char * filepath);
		void store_index(const char * filepath);
		void show_files()const;
		void show_dict()const;
	private:
		void get_files();
		void push_dict();
	private:
		string _dir;			
		vector<string> _files;
		map<string, int > _dict;
		unordered_map<string, set<int>> _hastbale;
//		SplitTool * _splitTool;	
};

}

#endif
