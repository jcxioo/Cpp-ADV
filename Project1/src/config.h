 ///
 /// @file    config.h
 /// @author  jcx(yxjcxstack@gmail.com)
 /// @date    2018-05-13 20:58:16
 ///
#ifndef __WD_CONFIG_H__
#define __WD_CONFIG_H__

#include "Mylogger.h"
#include <iostream>
#include <map>
#include <string>
using std::cout;
using std::endl;
using std::map;
using std::string;
namespace wd {
class Configuration
{
	
	public:
		Configuration();
		explicit
		Configuration(const string & filepath);
		map<string,string> & getConfigMap();

	private:
		string _filepath;
		map<string,string> _configMap;
};
}

#endif
