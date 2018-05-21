 ///
 /// @file    Noncopyable.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-05-10 00:11:11
 ///

#ifndef __WD_NONCOPYABLE_H__
#define __WD_NONCOPYABLE_H__

namespace wd
{
class Noncopyable
{
	protected:
	Noncopyable(){}
	~Noncopyable(){}
	Noncopyable(const Noncopyable & rhs) = delete;
	Noncopyable & operator = (const Noncopyable & ) = delete;
};
}//end of namespace wd

#endif
