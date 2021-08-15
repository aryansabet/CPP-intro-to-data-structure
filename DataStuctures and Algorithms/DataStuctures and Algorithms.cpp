

#include <iostream>
#include "Array.h"
#include <cassert>
#include <exception>


using std::cout; 


std::ostream& operator<<(std::ostream& os, const Array& a) {
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
	int indexOfLastElement = a.Size() - 1;
	for (int i = 0; i < indexOfLastElement; i++)
	{
		os << a[i] << ", ";
	}

	//now printing last element
	os << a[indexOfLastElement];

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
    try {
        Array a{ 3 };
        
        for (int i = 0; i < a.Size(); i++)
        {
            a[i] = i + 1;
        }
        cout << "Array a: " << a << '\n';
		Array b = a;
		cout << "Array a: " << a << '\n';
		cout << "Array b: " << b << '\n';

		b[0] = 80;

		cout << "Array a: " << a << '\n';
		cout << "Array b: " << b << '\n';



    }
    catch (const IndexOutOfBoundsException& e) {
        cout << "\n *** ERROR: Invalid index!! \n";
    }
}


