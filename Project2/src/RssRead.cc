 ///
 /// @file    RssRead.cc
 /// @author  jcx(yxjcxstack@gmail.com)
 /// @date    2018-05-21 23:54:04
 ///
 
#include "tinyxml2.h"
#include "Mylogger.h"

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

using namespace tinyxml2;

class RssRead
{
	XMLDocument doc;
	doc.LoadFile("");

	XMLElement * proot = doc.FirstChildElement("rss");
	XMLElement * pchannel = proot->FirstChildElement("channle");
	XMLElement * pitem = pchannel->FirstChildElement("item");
}

