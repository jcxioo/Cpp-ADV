 ///
 /// @file    testlogger.cc
 /// @author  jcx(yxjcxstack@gmail.com)
 /// @date    2018-04-16 10:52:41
 ///
 
#include "Mylogger.h"
#include <string>
#include <iostream>
#include <sstream>
using std::cout;
using std::endl;

void test(void)
{
	Mylogger::getInstance()->info("info message.");
	Mylogger::getInstance()->warn("warn message.");
	Mylogger::getInstance()->error("error message.");
	Mylogger::getInstance()->debug("debug message.");	
	
	Mylogger::destroy();
}
void test1(void)
{
	LogWarn("warn message.");
	LogError("Error message.");
	LogInfo("Info message.");
	LogDebug("debug message.");
}

int main(void)
{
	//test();
	test1();
	return 0;
}
