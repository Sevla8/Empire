#ifndef ARRAY_H
#define ARRAY_H

#include <assert.h>

template <class T>
class Array {
public:
	Array(int initialCapacity = 4);
	Array(const Array<T>& copy);
	~Array();
	int size() const;
	void add(const T& item);
	T& operator[](const int index);
	const T& operator[](const int index) const;
	bool operator==(const Array<T>& other);
	Array<T> operator=(const Array<T>& other);
	int imdexOf(const T& element);
private:
	T* array;
	int capacity;
	int nbElements;
	void resize(int newCapacity);
};

#endif
