 //
 /// @file    queue.cc
 /// @author  jcx(yxjcxstack@gmail.com)
 /// @date    2018-04-12 09:09:13
 ///
 
#include <iostream>

using std::cout;
using std::endl;

class Queue
{
	public:
		Queue(int size = 10)
		: _size(size)
		, _q(new int[_size]())
		, _front(0)
		, _rear(0)
		{
			cout << "Queue()" << endl;
		}

		void push(int q)
		{
			if(!full())	
			{
				_q[_rear] = q;
				cout << "_q[" << _rear 
					<< "] = " << _q[_rear] 
					<<endl;
				_rear++;
			}
		}

		void pop()
		{
			if(!empty())
			{
				
				_q[_front] = 0;
				_front++;
				cout << "pop()" << endl;
			}
		}

		void front()
		{
			cout << "front =" << _q[_front] << "\t";
		}

		void back()
		{
			cout << "back = " << _q[_rear-1] << endl;
		}

		bool full()
		{
		//	cout << "Queue is full." << endl;
			return _front == (_rear+1)%_size;		
		}
		bool empty()
		{
		//	cout << "Queue is empty." << endl;
			return _front == _rear;
		}


	private:
		int _size;
		int * _q;
		int _front;
		int _rear;

};

int main(void)
{
	Queue q;
	cout <<"empty?" << q.empty() << endl;
	q.push(1);
	cout <<"empty?" << q.empty() << endl;
	for(int idx = 2; idx != 10 ; ++idx)
	{
		q.push(idx);
	}
	cout <<"full?" << q.full() << endl;
	
	while(!q.empty())
	{
		q.front();
		q.pop();
	}
	cout <<"empty?" << q.empty() << endl;
	
	return 0;
}
