#include "stack.h"
#include "stdio.h"
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
	return !OK();
}

template <typename T>
T Stack<T>::pop(void)
{
	if (OK()) return NULL;
	if (size_) return data_[--size_];
	return NULL;
}

template <typename T>
int Stack<T>::OK(void)
{
	if (!this)		return 1;
	if (!capacity_)		return 2;
	if (size_ > capacity_)	return 3;
	return 0;
}

template <typename T>
bool Stack<T>::Init(size_t capacity)
{
	if (!capacity)	return false;
	if (!this)	return false;

	this->data_ = (T *) calloc(sizeof(T), this->capacity_ = capacity);
	this->size_ = 0;
	
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
