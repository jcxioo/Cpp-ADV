 ///
 /// @file    Configuration.cc
 /// @author  jcx(yxjcxstack@gmail.com)
 /// @date    2018-05-22 06:48:42
 ///
 
#ifndef __CONFIGURATION_H_
#define __CONFIGURATION_H_

#include "Mylogger.h"
#include "tinyxml2.h"
#include <iostream>
#include <string>
#include <map>
#include <set>
using std::cout;
using std::endl;
using std::map;
using std::set;

namespace wd
{
class Configuration
{
	public:
		Configuration(const string & filepath);
		map<string, string> & getConfigMap();
		set<string> getStopWordList();

	private:
		string _filepath;
		map<string, string> _configMap;
		set<string> _stopWordList;
};
};

#endif
