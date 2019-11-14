//#include "stack.h"

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
	this->datahash_ = 0;
	this->size_ = 0;
	this->capacity_ = 0;
}

template <typename T>
void Stack<T>::dump(void (*print) (const T *))
{
	printf("\033[45;1;1mStack %p dump:\033[0m\n\n", this);
	
	if (OK())
	{
		puts("\033[0;31m");
		printError();
		puts("\033[0m");
	}

	printf("\033[0;32mSize is	\t\t%lu\033[0m\n", size_);
	printf("\033[0;33mCapasity is	  \t%lu\033[0m\n", capacity_);
        printf("\033[0;34mData hash is	  \t%lX\033[0m\n", datahash_);

	if (print)
	{
		printf("\nData dump(by user-defined function):\n");
		for (size_t i = 0; i < size_; i++)
		{
			printf("[%lu] == ", i);
			print(&data_[i]);
		}
	}

	printf("\nData dump (in hexadecimal):\n");
	for (size_t i = 0; i < capacity_; i++)
		printf("[%lu] == %X\n", i, data_[i]);
	putchar('\n');
}
