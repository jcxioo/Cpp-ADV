 ///
 /// @file    testThreadpool.cc
 /// @author  jcx(yxjcxstack@gmail.com)
 /// @date    2018-05-10 07:23:05
 ///
 
#include "Threadpool.h"

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using std::cout;
using std::endl;
using namespace wd;

class MyTask
:public Task
{
	public:
		void process()
		{
			::srand(::clock());
			int number = ::rand() % 100;
			cout << ">>> produce a number = " << number << endl;
		}
};

int main(void)
{
	Threadpool threadpool(4,10);
	threadpool.start();
	unique_ptr<Task> ptask(new MyTask());

	int cnt = 20;
	while(cnt--)
	{
		cout << ">>> cnt = " << cnt << endl;
		threadpool.addTask(ptask.get());
	}

	threadpool.stop();
	return 0;
}
