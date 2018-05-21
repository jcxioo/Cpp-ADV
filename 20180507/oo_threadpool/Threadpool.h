 ///
 /// @file    Threadpool.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-07 15:21:35
 ///
 

#ifndef __WD_THREADPOOL_H__
#define __WD_THREADPOOL_H__


#include "TaskQueue.h"

#include <vector>
#include <memory>
using std::unique_ptr;
using std::vector;

namespace wd
{

class Task
{
public:
	virtual
	void process() =0;
};
 

class Thread;
class WorkerThread;
class Threadpool
{
	friend WorkerThread;
public:
	Threadpool(size_t threadNum, size_t queSize);
	~Threadpool();

	void start();
	void stop();
	void addTask(Task *);
private:
	Task * getTask();

	void threadFunc();
private:
	size_t _threadNum;
	size_t _queSize;
	vector<unique_ptr<Thread>> _threads;
	TaskQueue _taskQue;
	bool _isExit;
};

}//end of namespac wd


#endif
