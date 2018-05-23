 ///
 /// @file    offlinetest.cc
 /// @author  jcx(yxjcxstack@gmail.com)
 /// @date    2018-05-22 01:26:36
 ///
 
#include "Mylogger.h"
#include "MyConf.h"

#include <iostream>
using std::cout;
using std::endl;

using namespace wd;

int main(void)
{
	MyConf::getInstance()->init("../conf/my.conf"); 
	MyConf::getInstance()->show();
	
	
}
