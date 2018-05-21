 ///
 /// @file    Condition.cc
 /// @author  jcx(yxjcxstack@gmail.com)
 /// @date    2018-05-10 07:14:02
 ///
 
#include "Condition.h"
#include "MutexLock.h"

using namespace wd;

Condition::Condition(MutexLock & mutex)
: _mutex(mutex)
{
	pthread_cond_init(&_cond, NULL);
}

Condition::~Condition()
{
	pthread_cond_destroy(& _cond);
}

void Condition::wait()
{
	pthread_cond_signal(&_cond);
}

void Condition::notifyAll()
{
	pthread_cond_broadcast(&_cond);
}
