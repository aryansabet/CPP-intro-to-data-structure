#pragma once
//Header Guard

#include <ostream>
#include "StackOverflowException.h"
#include "Array.h"

// Stack Metaphor
// Last-in First-out (LIFO)
// reading book - phone calls - postman knock the door
// plate stack

// remember we said that arrays are foundation to implement more complex data structures
// use templates to generalize class
// think about operations
// use nested function calls to implement class
// stack operations :
//		push()
//			where to push? so we need to recognize where is the top of stack
//			which sometimes called stack pointer
//			updating stack pointer when we push is a key
//      Top var : the stack pointer index
//      pop()
//			inverse of push(). returning the top element that with popped
//			don't forget to update the Top index
//		Top()
//			access to only observe top stack element
//
//		*** Random access is not allowed ***
//			you can only access top element (LIFO)



template <typename T>
class Stack
{
	friend std::ostream& operator<<(std::ostream& os, const Stack<T>& stack) {
		os << "[";
		if (! stack.IsEmpty())
		{
			for (int i = stack.m_top; i >= 1 ; i--)
			{
				os << " " << stack.m_array[i] << ", ";
			}

			os << " " << stack.m_array[0];
		}
		os << "]";
		return os;
	}

private:
	Array<T> m_array; // object composition
	int m_top; // index of top element { -1 for empty array }
	
public:
	explicit Stack(int maxStackSize)
		//member initializer list:
		: m_top{ -1 }, m_array{ maxStackSize }
	{}
	//no need to add boilerplate code for Stack copy constructor or destructor
	//	1- cause we don't have pointer as attribute
	//  2- Array Class already has destructor  & copy constructor
	//  3- Default compiler-generated Stack's destructor invokes Array's destructor. same for copy ctor
	void Push(const T& element)
	{	
		// in case of pathological conditions, better throwing an exception than execute bogus code
		if (Size() >= MaxSize())
		{
			throw StackOverflowException{};
		}
		m_top++;
		m_array[m_top] = element;
	}

	T Pop() {
		// NOTE : We should add condition to check preventing underflow 
		T topElement = m_array[m_top];
		m_top--;
		return topElement;
	}

	const T& Top() const {
		return m_array[m_top];
	}

	int Size() const {
		//How many items stored in the Stack
		return (m_top + 1);
	}

	bool IsEmpty() const {
		return (Size() == 0);
	}

	int MaxSize() const {
		return m_array.Size();
	}

	void Clear() {
		m_top = -1;
	}


};

