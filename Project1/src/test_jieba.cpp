 ///
 /// @file    test_jieba.cpp
 /// @author  jcx(yxjcxstack@gmail.com)
 /// @date    2018-05-21 05:55:19
 ///
 
#include "WordSegmentation.hpp"
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

int main(void)
{
	string str = "结巴分词库的下载和应用";
	WordSegmentation wordSeg;
	vector<string> results = wordSeg(str);
	cout << "分词结果如下：" << endl;
	for(auto it = results.begin();
			it != results.end();
		++it)
	{
		cout << *it << endl;
	}
	return 0;
}
