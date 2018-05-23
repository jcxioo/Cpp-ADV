 //
 /// @file    MyConf.cc
 /// @author  jcx(yxjcxstack@gmail.com)
 /// @date    2018-05-21 19:27:35
 ///
 
#include "MyConf.h"
#include "Mylogger.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>

using std::ifstream;
using std::cout;
using std::endl;
using std::istringstream;

using namespace wd;

MyConf * MyConf::_pInstance = getInstance();

MyConf * MyConf::getInstance()
{ 
	if(NULL == _pInstance)
	{
		_pInstance = new MyConf;
		return _pInstance;
	}
	return _pInstance;
}

bool MyConf::init(const string & filename)
{
	ifstream ifs(filename.c_str());
	if(!ifs)
	{
		LogError("conf file read erro! ");	
		return false;
	}
	string line;
	while(getline(ifs,line))
	{
		istringstream iss(line);
		string key, value;
		iss >> key >> value;
		_map.insert(make_pair(key, value));
	}
	ifs.close();
	return true;
}

void MyConf::show()
{
	map<string, string>::const_iterator mit = _map.begin();
	for(;mit != _map.end(); ++mit)
	{
		cout << mit->first << " --> " << mit->second << endl;
	}
}

