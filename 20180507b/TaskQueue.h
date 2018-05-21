 /// @file    TaskQueue.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-10 02:43:51
 ///
#ifndef __WD_TASKQUEUE_H__
#define __WD_TASKQUEUE_H__

#include "MutexLock.h"
#include "Condition.h"
#include <queue>

using namespace wd;

class Task;
class TaskQueue
{
	public:
		using Type = Task *;
		TaskQueue(int queSize);
		
		bool full() const;
		bool empty() const;

		void push(Type & type);
		Type pop();
	private:
		size_t _queSize;
		std::queue<Type> _que;
		MutexLock _mutex;
		Condition _notFull;
		Condition _notEmpty;
};

#endif
