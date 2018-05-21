 ///
 /// @file    WordSegmentation.hpp
 /// @author  jcx(yxjcxstack@gmail.com)
 /// @date    2018-05-21 06:40:54
 ///
#ifndef __MY_WORD_SEGEMENTATION_H
#define __MY_WORD_SEGEMENTATION_H

#include "cppjieba/jieba.hpp"
#include <iostream>
#include <vector>
#include <string>
using std::cout;
using std::endl;
using std::vector;
using std::string;

const char *  DICT_PATH = "/home/jcx/cppjieba/dict/jieba.dict.utf8";
const char * const HMM_PATH = "/home/jcx/cppjieba/dict/hmm_model.utf8";
const char * const USER_DICT_PATH = "/home/jcx/cppjieba/dict/user.dict.utf8";
const char * const IDF_PATH = "/home/jcx/cppjieba/dict/idf.utf8";
const char * const STOP_WORD_PATH = "/home/jcx/cppjieba/dict/stop_words.utf8";
class WordSegmentation
{
	public:
		WordSegmentation()
		:_jieba(DICT_PATH,HMM_PATH,USER_DICT_PATH,IDF_PATH,STOP_WORD_PATH)
		{
			cout << "cppjieba init! " << endl;
		}
		vector<string> operator()(const string str)
		{
			vector<string> words;
			_jieba.CutALL(str,words);
		}
	private:
		cppjieba::jieba _jieba;
}

#endif
