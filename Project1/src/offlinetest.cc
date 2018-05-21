 ///
 /// @file    offlinetest.cpp
 /// @author  jcx(yxjcxstack@gmail.com)
 /// @date    2018-05-15 00:05:59
 //
 
#include "Mylogger.h"
#include "DictProducer.h"
#include "config.h"
#include <iostream>
using std::cout;
using std::endl;
using namespace wd;

int main(void)
{
	Configuration configuration("/home/jcx/cppgit/Project1/conf/my.conf");
	DictProducer dictProducer("/home/jcx/cppgit/Project1/data/english.txt");

	dictProducer.build_dict();
	dictProducer.build_index();
	dictProducer.store_dict("/home/jcx/cppgit/Project1/data/mydict.dat");
	LogInfo("dict build success!");
	dictProducer.store_index("/home/jcx/cppgit/Project1/data/myindex.dat");
	LogInfo("index build success!");

	return 0;
}
