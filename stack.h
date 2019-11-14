#ifndef STACK
#define STACK

#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdio.h>

typedef long unsigned Hashval;

enum Errcode {NOERR, NPTR, NCAP, FULL, HASH};

template <typename T>
class Stack
{
	private:
		//Hashval can1_;
		T *data_;
		Hashval datahash_;
	        size_t size_;
	        size_t capacity_;
		//Hashval can2_;

		Errcode OK(void);
	public:	
		bool push(T val);
		T pop(void);
		void dump(void (*print) (const T *) = nullptr);
		void printError();
		bool Init(size_t capacity = 1);
		void Delete();
};

static Hashval getHash(const void *beg, size_t len, size_t msize);

#include "stack.cpp"
#endif
