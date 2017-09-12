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

template <class T, size_t N>
struct block
{
    typedef T                   value_type;
    typedef value_type*         pointer;
    typedef const value_type*   const_pointer;
    typedef value_type&         reference;
    typedef const value_type&   const_reference;
    typedef ptrdiff_t           difference_type;
    typedef size_t              size_type;
    typedef pointer             iterator;
    typedef const_pointer       const_iterator;

    typedef reverse_iterator<const_iterator>    const_reverse_iterator;
    typedef reverse_iterator<iterator>          reverse_iterator;

    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }

    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

    iterator begin() { return data; }
    iterator end() { return data + N; }

    const_iterator begin() const { return data; }
    const_iterator end() const { return data + N; }

    reference operator[](size_type n) { return data[n]; }
    const_reference operator[](size_type n) const { return data[n]; }

    size_type size() const { return N; }
    T data[N];
    
    template <class T, size_t N>
    friend bool operator==(const block<T, N>& x, const block<T, N>& y)
    {
        for (size_t n = 0; n < N; ++n)
            if (x.data[n] != y.data[n])
                return false;
        return true;
    }

    template <class T, size_t N>
    friend bool operator<(const block<T, N>& x, const block<T, N>& y)
    {
        for (size_t n = 0; n < N; ++n)
            if (x.data[n] < y.data[n])
                return true;
            else if (y.data[n] > x.data[n])
                return false;
        return false;
    }
};



int main()
{
    int a[] = { 5,1,2,4,7 };
    vector<int> V;
    MySTL::copy(begin(a), end(a), MySTL::back_insert_iterator<decltype(V)>(V));
	return 0;
}