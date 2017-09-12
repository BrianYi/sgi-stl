#include <iostream>
#include "vector"
#include "MySTL.h"
using namespace std;
using namespace MySTL;

template <class Iterator, class Predicate>
Iterator my_find_if(Iterator beg, Iterator end, Predicate pred)
{
    Iterator first = beg;
    while (first != end)
    {
        if (pred(*first))
            break;
        first++;
    }
    return first;
}

int main()
{
    int a[] = { 5,1,2,4,7 };
    int *p = my_find_if(a, a + 5, even<int>());
	return 0;
}