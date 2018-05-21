 ///
 /// @file    String.cc
 /// @author  jcx(yxjcxstack@gmail.com)
 /// @date    2018-04-11 08:55:18
 ///
 
#include <iostream>
#include <string>
#include <string.h>
using std::cout;
using std::endl;

class String
{
	public:
		String ()
		: _pstr (new char[1]())//加小括号后会自动初始化为0，不必再赋0
		{
			//*_pstr ='0';
			cout << "String " << endl;
		}

		String (const char *pstr)	
		: _pstr (new char[strlen(pstr)+1]())
		{
			strcpy(_pstr, pstr);
			cout << "String(const char *pstr)" << endl;
			//	<< pstr <<endl;
		}
		
		String(const String & rhs)//复制构造函数
		: _pstr(new char[strlen(rhs._pstr)+1]())
		{
			strcpy(_pstr, rhs._pstr);
			cout << "String(const String & rhs))" <<endl;
		}
	
		String & operator = (const String & rhs)//三部曲
		{
			cout << "String & operator" << endl;
			if(this != &rhs)
			{
				delete [] _pstr;
				_pstr = new char[strlen(rhs._pstr) + 1]();
				strcpy(_pstr, rhs._pstr);
			}
			return *this;	
		}
		
		~String()
		{
			delete [] _pstr;
			cout << "~String" << endl;
			
		}
		void print()
		{
			cout << "pstr = "<< _pstr << endl; 
		}
	private:
		char * _pstr;
};


int main(void)
{
	String str1;
	str1.print();

	String str2 = "Hello world";
	String str3("wangdao");

	str2.print();
	str3.print();

	String str4 = str3;
	str4.print();
		
	str4 = str2;
	str4.print();
	
	return 0;
}
