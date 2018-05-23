 ///
 /// @file    pagelib.cc
 /// @author  jcx(yxjcxstack@gmail.com)
 /// @date    2018-05-22 00:46:25
 ///
 
#include "Mylogger.h"
#include "tinyxml2.h"

#include <iostream>
using std::cout;
using std::endl;

//using namespace tinyxml2;


using namespace wd;
class PageLib
{
	public:
		PageLib(MyConf & conf,
				DirScanner & dirScanner
				FileProcessor & fileProcessor)
		: _conf(conf)
		, _dirScanner(dirScanner)
		, _file
		{

		}
		
		void create();
		void store();


	private:
		Myconf  & _conf;
		DirScanner & _dirScanner;
		vector<string> _vecFilesfiles;
		Map<int, pair<int, int>> _offsetLib;

};

