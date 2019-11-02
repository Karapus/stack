#ifndef STACK
#define STACK

#include <stdlib.h>
#include <assert.h>

template <typename T>
class Stack
{
	private:
        
	T *data_;
        size_t size_;
        size_t capacity_;
	int OK(void);
	
	public:
	
	bool push(T val);
	T pop(void);
	void dump();
	int getError();
	bool Init(size_t capacity = 1);
	void Delete();
};

#endif
