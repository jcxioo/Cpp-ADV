 ///
 /// @file    Configuration.cc
 /// @author  jcx(yxjcxstack@gmail.com)
 /// @date    2018-05-22 06:58:10
 ///
 
#include "Mylogger.h"
#include "tinyxml2.h"
#include "Configuration.h"
#include <iostream>
using std::cout;
using std::endl;
using std::map;

Configuration::Configuration(const string & filepath)
{
	LogInfo("debug Configuration()");
}
