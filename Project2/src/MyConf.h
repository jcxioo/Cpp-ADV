 ///
 /// @file    MyConf.h
 /// @author  jcx(yxjcxstack@gmail.com)
 /// @date    2018-05-21 19:29:04
 ///
 
#ifndef __MYCONF_H__
#define __MYCONF_H__
#include <iostream>
#include <string>
#include <map>

using std::string;
using std::map;

namespace wd
{

class MyConf
{
	public:
	static MyConf * getInstance();
	map<string, string> & getMap(){return _map; }
	bool init(const string & filename);
	void show();

	private:
		MyConf(){}
		~MyConf(){}

	private:
		map<string, string> _map;
		static MyConf * _pInstance;

};

};
#endif
