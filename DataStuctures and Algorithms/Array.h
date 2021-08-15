#pragma once
//Header Guard


#include <iostream>
#include <utility>
#include "IndexOutOfBoundsException.h"

template <typename T>
class Array
{
	friend void swap(Array& a, Array& b) noexcept{
		using std::swap;
		//Memberwise swap
		swap(a.m_ptr, b.m_ptr);
		swap(a.m_size, b.m_size);
		//Remember to make it noexcept
	}
private:
	//Direct Member Initialization C++11
	int* m_ptr{ nullptr };
	int m_size{ 0 };

	bool IsValidIndex(int index) const{
		//what if it was not const?
		//Bounds Checking to avoid overflow
		return (index >= 0) || (index < m_size);
	}

public: // Interface between this data structures with users
	Array() = default;//Create Empty Array

	explicit Array(int size) { 
		//Use explicit keyword with one-argument constructors to make your code safer
		if (size != 0) {
			m_ptr = new T[size] {};
			//{} for Zero-init instead of some Garbage initial values
			// safe init
			m_size = size;
		}
	}

	// Copy initialization : using Copy Constructor 
	// default Copy Constructor : member-wise Copy (simply copying peer to peer members of a to b)
	// that will copy the same address to pointer member variables : Shallow Copy
	// Modifications to b are reflected to a - here is the Bug!
	// When object b goes out of scope in main function, delete[] b.m_ptr destructor will do the job
	// but!! after a goes out of scope, delete[] a.m_ptr will try to free the memory which is already free.
	// Double Delete Bug - Subtle memory bugs with shallow copies
	// solution 1:side steping the problem with deleting Compiler-generated copy constructor
	// Array(const Array& lhs) = delete;
	// solution 2 : deep copy -distinct arrays - clone & make new independent array
	Array(const Array& rhs) {
		if (!rhs.IsEmpty()) {
			m_size = rhs.m_size;
			m_ptr = new T[m_size] {};

			for (int i = 0; i < m_size; i++)
			{
				m_ptr[i] = rhs.m_ptr[i];
			}
		}

	}

	// Move Semantics : transfer without copying 
	// to avoid expensive copies
	// better performance when returning from function
	// Move constructor : enables move semantics
	// Moving Arrays : Re-assign pointers (steal the date)
	// no memory allocation
	// just changing the ownership of pointer from source to destination
	Array(Array&& source) {
		// Array&& : R-VALUE REFERENCE 
		// Temporary object: Can safely steal the data from it

		//Transfer ownership from source
		m_ptr = source.m_ptr;
		m_size = source.m_size;

		//Clear source : safe code
		source.m_ptr = nullptr;
		source.m_size = 0;
		//fast & cheap! no memory alloc. no deep copy.
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
		if (!Array::IsValidIndex(index)) {
			//Protection for buffer overruns
			throw IndexOutOfBoundsException{};
		}

		return m_ptr[index];
	}

	int operator[](int index) const {
		//Granting Read-only Access to Array Elements
		if (!IsValidIndex(index)) {
			//Protection for buffer overruns
			throw IndexOutOfBoundsException{};
		}
			
		return m_ptr[index];
	}

	Array& operator=(Array rhs) {
		//Array& operator=(const Array& rhs) {
		// Prevent self-assignment (x = x)
		//if (&rhs != this) {}
			//1 - do the copy
			//2 - Don't forget to release the previous array block
			//3 - Implement proper deep-copy form rhs to this
			//but ...
			 
			// Copy-and-swap Idiom
			// we need to Deep Copy: Reuse Copy constructor
			// we copy a to b. already reached copy part of copy-and-swap
			// the we swap it to t. there is the swap part.
			// after that we need to destruct the b.
			// so we need : 1- copy constructor: it happens cause used pass-by-value argument
			//              2- swap function (memberwise swap)
			//              3- destructor : implicitly called when =function reached out of scope
		
		swap(*this, rhs);
		return *this;
	}//destructor of Array rhs called

};

