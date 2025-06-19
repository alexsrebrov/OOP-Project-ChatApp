#pragma once
#include <iostream>
#define TT template<typename T>

TT
class MyVector
{
public:
	MyVector();
	MyVector(size_t cap);
	MyVector(const MyVector& other);
	MyVector& operator=(const MyVector& other);
	MyVector(MyVector&& other);
	MyVector& operator=(MyVector&& other);
	~MyVector();

	size_t getSize() const;
	size_t getCap() const;

	MyVector& add(const T& el);
	MyVector& add(T&& el);
	void remove(size_t index);
	void remove(const T& el);
	size_t findIndex(const T& el);

	void printAll() const;
	bool empty() const;
	MyVector& clear();

	const T& operator[](size_t index) const;
	T& operator[](size_t index);
private:
	void free();
	void copyFrom(const MyVector& other);
	void moveFrom(MyVector&& other);
	void resize(size_t newCap);

	T* data;
	size_t cap;
	size_t size;
};




TT
inline MyVector<T>::MyVector() :size(0),cap(10)
{
	data = new T[cap];
}

TT
inline MyVector<T>::MyVector(const MyVector& other)
{
	copyFrom(other);
}
TT
inline MyVector<T>::MyVector(size_t cap) :size(0), cap(cap)
{
	data = new T[cap];
}

TT
inline MyVector<T>& MyVector<T>::operator=(const MyVector& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

TT
inline MyVector<T>& MyVector<T>::operator=(MyVector&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

TT
inline MyVector<T>::~MyVector()
{
	free();
}

TT
inline MyVector<T>::MyVector(MyVector&& other)
{
	moveFrom(std::move(other));
}

TT
inline size_t MyVector<T>::getSize() const
{
	return size;
}

TT
inline size_t MyVector<T>::getCap() const
{
	return cap;
}

TT
inline MyVector<T>& MyVector<T>::add(const T& el)
{
	if (size >= cap) resize(cap * 2);
	data[size++] = el;
	return *this;
}


TT
inline MyVector<T>& MyVector<T>::add(T&& el)
{
	if (size >= cap) resize(cap * 2);
	data[size++] = el;
	return *this;
}

TT
inline void MyVector<T>::remove(size_t index)
{
	if (index >= size) throw std::out_of_range("Index out of range");
	std::swap(data[index], data[size - 1]);
	size--;
}

TT
inline void MyVector<T>::remove(const T& el)
{
	size_t index = findIndex(el);
	remove(index);
}

TT
inline size_t MyVector<T>::findIndex(const T& el)
{
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == el) return i;
	}
	throw std::invalid_argument("Element not found");
}

TT
inline void MyVector<T>::printAll() const
{
	for (size_t i = 0; i < size; i++)
	{
		std::cout << data[i] << std::endl;
	}
}
TT
inline bool MyVector<T>::empty() const
{
	return !size;
}

TT
inline MyVector<T>& MyVector<T>::clear()
{
	size = 0;
	return *this;
}

TT
inline const T& MyVector<T>::operator[](size_t index) const
{
	if (index >= size || empty()) throw std::out_of_range("Index out of range");
	return data[index];
}

TT
inline T& MyVector<T>::operator[](size_t index)
{
	if (index >= size || empty()) throw std::out_of_range("Index out of range");
	return data[index];
}

TT
inline void MyVector<T>::free()
{
	delete[] data;
	data = nullptr;
	size = cap = 0;
}

TT
inline void MyVector<T>::copyFrom(const MyVector& other)
{
	cap = other.cap;
	size = other.size;
	data = new T[cap];
	for (size_t i = 0; i < size; i++)
	{
		data[i] = other.data[i];
	}
}


TT
inline void MyVector<T>::moveFrom(MyVector&& other)
{
	data = other.data;
	other.data = nullptr;
	size = other.size;
	cap = other.cap;
	other.size = other.cap = 0;
}

TT
inline void MyVector<T>::resize(size_t newCap)
{
	T* res = new T[newCap];
	for (size_t i = 0; i < size; i++)
	{
		res[i] = data[i];
	}
	delete[] data;
	cap = newCap;
	data = res;
}

