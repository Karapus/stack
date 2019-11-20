//#include "stack.h"

template <typename T>
bool Stack<T>::push(T val)
{
	if (OK()) return false;

	if (this->size_ == this->capacity_)
		this->resize();

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
	if (!this)			return NPTR;
	if (!capacity_)			return NCAP;
	if (size_ > capacity_)		return FULL;
	if (datahash_ != getHash(data_, size_, sizeof(T)))
					return HASH;
	if (can1_ != can2_)		return SCAN;
	if (data_[-1] != data_[capacity_])
					return DCAN;
//	if (getHash(&data_, (char *)&stackhash_ - (char *)&data_, sizeof(char)) != stack)
	return NOERR;
}

template <typename T>
bool Stack<T>::resize(void)
{
	if (OK()) return false;
	
	T* new_data = new T[(capacity_ *= 2) + 2];
	if (!new_data)
		return false;

	memcpy(new_data, data_ - 1, sizeof(T) * (this->size_ + 1));

	delete[] (data_ - 1);
	data_ = new_data + 1;
	data_[capacity_] = data_[-1];
	
	if (OK()) return true;
	return false;
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
		case SCAN:
			fprintf(stderr, "Stack structure is overrided");
			break;
		case DCAN:
			fprintf(stderr, "Stack data is overrided");
			break;
	}
}

template <typename T>
bool Stack<T>::Init(size_t capacity)
{
	if (!capacity)	return false;
	if (!this)	return false;

	this->capacity_ = 1;
	this->data_ = new T[capacity + 2] + 1;
	this->data_[-1] = this->data_[this->capacity_] = rand() % (1<<(sizeof(T) * 8)) + 1;
	
	this->size_ = 0;
	this->can1_ = this->can2_ = rand() % UCHAR_MAX + 1; 
	this->datahash_ = 0;
	return !OK();
}

template <typename T>
void Stack<T>::Delete()
{
	delete[] (this->data_ - 1);
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

	printf("\033[0;33mStack canary is \t%X\033[0m\n", can1_ & 0xFF);
	printf("\033[0;32mSize is	\t\t%lu\033[0m\n", size_);
	printf("\033[0;36mCapasity is	  \t%lu\033[0m\n", capacity_);
        printf("\033[0;34mData hash is	  \t%lX\033[0m\n", datahash_);
//	printf("\033[0;35mStack hash is   \t%lX\033[0m\n", stackhash_);
	printf("\033[0;33mStack canary is \t%X\033[0m\n", can2_ & 0xFF);
	
	if (print)
	{
		printf("\nData dump(by user-defined function):\n");
		for (size_t i = 0; i < size_; i++)
		{
			printf("[%lu] == ", i);
			print(&data_[i]);
		}
	}
	
	printf("\n\033[0;33mData canary is \t%X\033[0m\n", data_[-1]);

	printf("Data dump (in hexadecimal):\n");
	for (size_t i = 0; i < capacity_; i++)
		printf("[%lu] == %X\n", i, data_[i]);
	printf("\033[0;33mData canary is \t%X\033[0m\n", data_[capacity_]);
}
