

#include <iostream>
#include "Array.h"
#include <cassert>
#include <exception>
#include <vector>
#include "Stack.h"
#include "List.h"

using std::cout; 


constexpr int kNotFound = -1;
// const int with compile time initialization 
// why -1?
int LinearSearch(int element, const int* v, int size) {
	// Complexity:
	//	O(N)
	//	which is so bad in Asymptotic Analysis.
	// v : observing pointer
	for (int i = 0; i < size; i++)
	{
		if (v[i] == element)
		{
			return i;
		}
	}
	return kNotFound;
}

int BinarySearch(int element, const int* v, int size) {
	// Complexity:
	//	progressive cut the space of problem(array) to half
	//	O(log(N))
	// Requirement of BinarySearch : array must me sorted.
	// Active search region:
	int left = 0;
	int right = size - 1;
	//what if we don't use (-1): subtle bug 
	//initial to search the hole input array

	while (left <= right) { //why?
		int middle = (left + right) / 2;
		//the inital array is halved at each iteration
		//loop with divide the search domain in half at each step

		if (v[middle] == element) {
			return middle;
		}
		else if (v[middle] < element) {
			// search in right half
			left = middle + 1;
		}
		else if (v[middle] > element) {
			// search in left half
			right = middle - 1;
		}
	}

	return kNotFound;
}
std::ostream& operator<<(std::ostream& os, const Array<int>& a) {
	// Overloading insertion operator for array class
	// os : Output stream (print target) (generic output stream object)
	//      which enables you even fine to work with other buffers
	//		for example output file stream or clog & cerr
	// a  : object to print (source)
	// return type ostream enables chained calls to insertion operator overloads
	// which is extensible to your own classes & follow same patternas this
	// (cout<<age<<name<<...;int,string)

	// here we need to Format Array

	os << "[";
	if (! a.IsEmpty())
	{
		int indexOfLastElement = a.Size() - 1;
		for (int i = 0; i < indexOfLastElement; i++)
		{
			os << a[i] << ", ";
		}

		//now printing last element
		os << a[indexOfLastElement];
	}
	os << "]";
	return os;
	// but what if we use m_ptr[i] instead of a[i] for perfectionism to reduce overhead?
	// then we need to friend this function to the class
}

int main()
{
    

    //Array a{};
    //assert(a.IsEmpty());

    //Array b{ 10 };
    //assert(!b.IsEmpty());
    //ASan
    //address sanitizer
    //clang++ -std=c++14 -fsanitize=address -g -o1 Array1.cpp
    //to spot the memory leak bug
  //  try {
  //      Array<int> a{ 3 };
  //      
  //      for (int i = 0; i < a.Size(); i++)
  //      {
  //          a[i] = i + 1;
  //      }
  //      
		//Array<int> b;
		//cout << "Array a: " << a << '\n';
		//cout << "Array b: " << b << '\n';

		//b = a;

		//cout << "Array a: " << a << '\n';
		//cout << "Array b: " << b << '\n';



  //  }
  //  catch (const IndexOutOfBoundsException& e) {
  //      cout << "\n *** ERROR: Invalid index!! \n";
  //  }
	//std::vector<int> v{ 11,22,33,44,55 };
	////int pos = LinearSearch(44, v.data(), v.size());
	//int pos = BinarySearch(44, v.data(), v.size());
	//if (pos == kNotFound){
	//	cout << "Element not found!\n";
	//}
	//else {
	//	cout << "index of Element is " << pos << ".\n";
	//}

	//Stack<int> myStack{ 10 };
	//assert(myStack.IsEmpty());
	//assert(myStack.MaxSize() == 10);

	//myStack.Push(10);
	//myStack.Push(9);
	//assert(myStack.Size() == 2);
	//cout << myStack << std::endl;
	//myStack.Pop();
	//cout << myStack << std::endl;
	
	List<int> l{};
	cout << " Created an empty list: " << l << "\n\n";

	cout << " Inserting some elements...\n";
	l.InsertHead(10);
	l.InsertHead(64);
	l.InsertHead(80);
	l.InsertHead(77);
	cout << " Current list: " << l << "\n\n";

	cout << " Inserting a new element (500) after node with value 64.\n";
	auto pos = l.Find(64);
	l.InsertAfter(pos, 500);
	cout << " Current list: " << l << "\n\n";

	cout << " Removing current head.\n";
	l.RemoveHead();
	cout << " Current list: " << l << "\n\n";

	cout << " Clearing the whole list.\n";
	l.Clear();
	cout << " Current list: " << l << "\n\n";
}


