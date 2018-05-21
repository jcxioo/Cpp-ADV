///
/// @file    config.cpp
/// @author  jcx(yxjcxstack@gmail.com)
/// @date    2018-05-14 00:51:15
///

#include "Mylogger.h"
#include "config.h"

#include <iostream>
#include <map>
#include <string>
#include <fstream>

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::fstream;
using std::ifstream;
using std::istringstream;

using namespace wd;

//Configuration::Configuration(){}
Configuration::Configuration(const string & filepath)
: _filepath(filepath)
{
	LogInfo("debug Configuration()");
}

map<string, string> & Configuration::getConfigMap()
{
	ifstream confifs(_filepath);
	LogInfo(_filepath);

	if(!confifs)
	{
		LogError("ifstream open error!");
		return _configMap;
	}
	string word1;
	string word2;
	char tmp[1000];
	while(confifs.getline(tmp,1000))
	{
//		confifs.getline(tmp,1000);
		string line(tmp);
		size_t pos = line.find('=');
		if(pos == string::npos) return _configMap;
		string word1 = line.substr(0,pos);
	LogInfo(word1);
		string word2 = line.substr(pos + 1);
	LogInfo(word2);
		_configMap.insert(std::make_pair(word1,word2));
	cout << word1 << endl;
	cout << _configMap[word1] << endl ;
	}
	cout << _configMap["mydict"] << endl ;
	confifs.close();
	return _configMap;
} 
