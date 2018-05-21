 ///
 /// @file    WorkerThread.h
 /// @author  jcx(yxjcxstack@gmail.com)
 /// @date    2018-05-10 05:33:31
 ///
 
#ifndef __WD_WORKERTHREAD_H__
#define __WD_WORKERTHREAD_H__

#include "Thread.h"
#include "Threadpool.h"

#include <iostream>
using std::cout;
using std::endl;

using namespace wd;

class WorkerThread
:public Thread
{
	public:
		WorkerThread(Threadpool & threadpool)
		: _threadpool(threadpool)
		{
			cout << "WorkerThread()" << endl;
		}
	
		~WorkerThread()
		{cout << "~WorkerThread()" << endl;}
	private:
		void run()
		{
			_threadpool.threadFunc();
		}
		Threadpool & _threadpool;
};

#endif
