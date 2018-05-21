 ///
 /// @file    TaskQueue.cc
 /// @author  jcx(yxjcxstack@gmail.com)
 /// @date    2018-05-10 05:00:05
 ///

#include "TaskQueue.h"
#include <iostream>
using std::cout;
using std::endl;

using namespace wd;

TaskQueue::TaskQueue(int queSize)
: _queSize(queSize)
, _mutex()
, _notFull(_mutex)
, _notEmpty(_mutex)
{}

bool TaskQueue::full() const
{
	return _queSize == _qus.size();
}

bool TaskQueue::empty() const
{
	return 0 == _que.size();
}

void TaskQueue::push(Type & elem)
{
	MutexLockGuard autoLock(_mutex);
	while(full())
	{
		_notFull.wait();
	}
	_que.push(elem);
	_notEmpty.notify();
}

TaskQueue::Type TaskQueue::pop()
{
	MutexLockGuard autoLock(_mutex);
	while(empty())
	{
		_notEmpty.wait();
	}
	Type tmp = _que.front();
	_que.pop();
	_notFull.notify();
	return tmp;
}



