#pragma once
#include <iostream>
class Array
{
private:
	//Direct Member Initialization C++11
	int* m_ptr{ nullptr };
	int m_size{ 0 };
public: // Interface between this data structures with users
	Array() = default;//Create Empty Array

	explicit Array(int size) { 
		//Use explicit keyword with one-argument constructors to make your code safer
		if (size != 0) {
			m_ptr = new int[size] {};
			//{} for Zero-init instead of some Garbage initial values
			// safe init
			m_size = size;
		}
	}

	~Array() {
		delete[] m_ptr;
		// what if array was empty?
		// delete[] nullptr is safe
		// delete[] is releasing Array hole memory block
		
	}

	int Size() const {
		// const is to don't modify the internal state of array object
		// const returns read-only properties of the array object
		return m_size;
	}

	bool IsEmpty() const {
		return (m_size == 0);
	}

	int& operator[](int index) {
		// Allowing external access to the array content
		// return with refrence to avoid int main() compilation error on line 22
		// (a[0] = 10;)(expression is not assignable)
		return m_ptr[index];
	}

	int operator[](int index) const {
		//Granting Read-only Access to Array Elements
		return m_ptr[index];
	}
};

