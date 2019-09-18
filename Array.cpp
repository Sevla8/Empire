#include "Array.h"

template <class T>
Array<T>::Array(int intitialCapacity) {
	this->capacity = intitialCapacity;
	this->nbElements = 0;
	this->array = new T[this->capacity];
}

template <class T>
Array<T>::Array(const Array<T>& copy) {
	this->capacity = copy.capacity;
	this->nbElements = copy.nbElements;
	this->array = new T[this->capacity];
	for (int i = 0; i < this->nbElements; i += 1)
		this->array[i] = copy.array[i];
}

template <class T>
Array<T>::~Array() {
	delete[] this->array;
}

template <class T>
void Array<T>::add(const T& item) {
	assert(this->nbElements <= this->capacity);
	if (this->nbElements == this->capacity)
		this->resize(this->capacity*2);
	this->array[this->nbElements] = item;
	this->nbElements += 1;
}

template <class T>
void Array<T>::resize(int newCapacity) {
	this->capacity = newCapacity;
	T* newArray = new T[this->capacity];
	for (int i = 0; i < this->capacity; i += 1)
		newArray[i] = this->array[i];
	delete[] this->array;
	this->array = newArray;
}

template <class T>
T& Array<T>::operator[](const int index) {
	assert(index < this->nbElements);
	assert(index >= 0);
	return this->array[index];
}

template <class T>
const T& Array<T>::operator[](const int index) const {
	assert(index < this->nbElements);
	assert(index >= 0);
	return this->array[index];
}

template <class T>
bool Array<T>::operator==(const Array<T>& other) {
	if (this == &other)
		return true;
	if (this->nbElements != other.nbElements)
		return false;
	for (int i = 0; i < this->nbElements; i += 1) {
		if (this->array[i] != other.array[i])
			return false;
	}
	return true;
}

template <class T>
Array<T> Array<T>::operator=(const Array<T>& other) {
	if (this == &other)
		return this;
	this->nbElements = other.nbElements;
	if (this->capacity < other.nbElements) {
		delete[] this->array;
		this->capacity = other.capacity;
		this->array = new T[capacity];
	}
	for (int i = 0; i < this->nbElements; i += 1) 
		this->array[i] = other.array[i];
	return *this;
}

template <class T>
int Array<T>::imdexOf(const T& element) {
	int a = 0;
	int b = this->nbElements;
	while (a < b) {
		int c = (a+b) / 2;
		if (element < this->array[c])
			b = c;
		else if (element > this->array[c])
			a = c;
		else 
			return c;
	}
	return -1;
}
