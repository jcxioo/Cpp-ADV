 ///
 /// @file    Mylogger.cc
 /// @author  jcx(yxjcxstack@gmail.com)
 /// @date    2018-04-16 09:18:23
 ///
#include "Mylogger.h" 

#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Priority.hh>

#include <iostream>
using  std::cout;
using std::endl;

Mylogger * Mylogger::_pInstance = NULL;

Mylogger * Mylogger::getInstance()
{
	if( NULL  == _pInstance)
	{
		_pInstance = new Mylogger();
	}
	return _pInstance;
}

void Mylogger::destroy()
{
	if(_pInstance)
	{
		delete _pInstance;
	}
}


Mylogger::Mylogger()
: _root(log4cpp::Category::getRoot())
{
	log4cpp::PatternLayout * pt1 = new log4cpp::PatternLayout();
	pt1->setConversionPattern("[%d]  [%p] : %m%n");
	
	log4cpp::PatternLayout * pt2 = new log4cpp::PatternLayout();
	pt2->setConversionPattern("[%d]  [%p] : %m%n");
	
	log4cpp::OstreamAppender * OstreamAppender = new log4cpp::OstreamAppender("OstreamAppender", &cout);
	OstreamAppender->setLayout(pt1);

	log4cpp::FileAppender * fileAppender = new log4cpp::FileAppender("fileAppender","test.log");//实际工作通过配置文件
	fileAppender->setLayout(pt2);
	
	_root.addAppender(OstreamAppender);
	_root.addAppender(fileAppender);
	_root.setPriority(log4cpp::Priority::DEBUG);
	
}
Mylogger::~Mylogger()
{
	cout << "~Myloggrt" << endl;
	log4cpp::Category::shutdown();
	 
}


void Mylogger::warn(const char * msg)
{
	_root.warn(msg);
}
void Mylogger::error(const char * msg)
{
	_root.error(msg);
}
void Mylogger::info(const char * msg)
{
	_root.info(msg);
}
void Mylogger::debug(const char * msg)
{
	_root.debug(msg);
}


