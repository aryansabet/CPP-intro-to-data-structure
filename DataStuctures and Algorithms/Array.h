#pragma once
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

	

	int Size() const {
		// const is to don't modify the internal state of array object
		// const returns read-only properties of the array object
		return m_size;
	}

	bool IsEmpty() const {
		return (m_size == 0);
	}
};

