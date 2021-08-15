

#include <iostream>
#include "Array.h"
#include <cassert>

int main()
{
    Array a{};
    assert(a.IsEmpty());

    Array b{ 10 };
    assert(!b.IsEmpty());



}


