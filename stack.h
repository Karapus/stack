#ifndef STACK
#define STACK

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef long unsigned Hashval;

enum Errcode {NOERR, NPTR, NCAP, FULL, HASH, SCAN, DCAN};

template <typename T>
class Stack
{
	private:
		char can1_;
		T *data_;
		Hashval datahash_;
	        size_t size_;
	        size_t capacity_;
		Hashval stackhash_;
		char can2_;

		Errcode OK(void);
		bool resize(void);
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
