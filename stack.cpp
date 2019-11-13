#include "stack.h"

template <typename T>
bool Stack<T>::push(T val)
{
	if (OK()) return false;

	if (this->size_ == this->capacity_)
	{
		this->data_ = (T *) realloc(this->data_, this->capacity_ *= 2);
		assert(this->capacity_);
	}
	this->data_[this->size_++] = val;
	this->datahash_ = getHash(this->data_, this->size_, sizeof(T));
	return !OK();
}

template <typename T>
T Stack<T>::pop(void)
{
	if (OK()) return NULL;
	if (size_)
	{
		this->datahash_ = getHash(this->data_, this->size_ - 1, sizeof(T));
		return data_[--size_];
	}
	return NULL;
}

template <typename T>
Errcode Stack<T>::OK(void)
{
	if (!this)		return NPTR;
	if (!capacity_)		return NCAP;
	if (size_ > capacity_)	return FULL;
	if (datahash_ != getHash(this->data_, this->size_, sizeof(T))) return HASH;

	return NOERR;
}

static Hashval getHash(const void *beg, size_t len, size_t msize)
{
	const  Hashval RANGE = ULONG_MAX - 59 + 1;
        static Hashval base = (rand() % UCHAR_MAX) + 1;
        const unsigned char *ptr = (const unsigned char *) beg;
        Hashval hash = 0;
	len *= msize;
        while (ptr < beg + len)
                hash = ((hash * base) + *(ptr++)) % RANGE;
        return hash;
}

template <typename T>
void Stack<T>::printError()
{
	switch (OK())
	{
		case NOERR:
			fprintf(stderr, "Stack %p is Ok\n", this);
			break;
		case NPTR:
			fprintf(stderr, "Stack is not allocated\n");
			break;
		case NCAP:
			fprintf(stderr, "Stack capacity is zero\n");
			break;
		case FULL:
			fprintf(stderr, "Stack is oferflowed\n size == %ld, capacity == %ld\n", size_, capacity_);
			break;
		case HASH:
			fprintf(stderr, "Stack data is modified from outside\n");
			break;
	}
}

template <typename T>
bool Stack<T>::Init(size_t capacity)
{
	if (!capacity)	return false;
	if (!this)	return false;

	this->data_ = (T *) calloc(sizeof(T), this->capacity_ = capacity);
	this->size_ = 0;
	//this->can1_ = this->can2_ = ;
	this->datahash_ = 0;
	return !OK();
}

template <typename T>
void Stack<T>::Delete()
{
	free(this->data_);
	this->data_ = nullptr;
	this->size_ = 0;
	this->capacity_ = 0;
}

template <typename T>
void Stack<T>::dump()
{
	printf("Stack %p dump:\n", this);
	
	if (OK())
	{
		puts("\033[0;31m");
		printError();
		puts("\033[0m");
	}


}
