#pragma once
#include <iostream>
using namespace std;

namespace MySTL {

    template <class Iterator, class T>
    Iterator find(Iterator first, Iterator last, const T& value)
    {
        while (first != last && *first != value)
            ++first;
        return first;
    }

    struct int_node
    {
        int val;
        int_node* next;
    };

    int_node* CreateLinkList()
    {
        int_node *head = new int_node;
        int_node *p = head;
        int_node *s = nullptr;
        int c;
        while (std::cin >> c, c != -1)
        {
            s = new int_node;
            s->val = c;
            s->next = nullptr;
            p->next = s;
            p = p->next;
        }
        return head;
    }

    template <class Iterator>
    void printLinkList(Iterator head)
    {
        Iterator start = ++head;
        while (start != nullptr)
        {
            cout << start->val << " ";
            start++;
        }
        cout << endl;
    }

    template <class InputIterator, class OutputIterator>
    OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
    {
        for (; first != last; ++result, ++first)
            *result = *first;
        return result;
    }

    template <class T> class ostream_iterator
    {
    private:
        std::ostream* os;
        const char* string;
    public:
        ostream_iterator(std::ostream& s, const char* c = 0) :os(&s), string(c) {}
        ostream_iterator(const ostream_iterator& i) :os(i.os), string(i.string) {}
        ostream_iterator& operator=(const ostream_iterator& i)
        {
            os = i.os;
            string = i.string;
            return *this;
        }
        ostream_iterator<T>& operator=(const T& value)
        {
            *os << value;
            if (string) *os << string;
            return *this;
        }

        ostream_iterator<T>& operator*() { return *this; }
        ostream_iterator<T>& operator++() { return *this; }
        ostream_iterator<T>& operator++(int) { return *this; }
    };

    template <class ForwardIterator, class T>
    void replace(ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value)
    {
        for (; first != last; ++first)
            if (*first == old_value)
                *first = new_value;
    }

    template <class ForwardIterator>
    ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last)
    {
        if (first == last)
            return last;
        ForwardIterator next = first;
        while (++next != last)
        {
            if (*first == *next)
                return first;
            first = next;
        }
        return last;
    }

    template <class BidirectionalIterator, class OutputIterator>
    OutputIterator reverse_copy(BidirectionalIterator first, BidirectionalIterator last, OutputIterator result)
    {
        while (first != last)
        {
            --last;
            *result = *last;
            ++result;
        }
        return result;
    }

    struct Iterator
    {
        // operator*()
        // operator++()
    };

    struct InputIterator : public Iterator
    {
        // operator!=()
        // operator->()
        // operator++(int)
    };

    struct OutputIterator : public Iterator
    {
        // operator=()
        // operator++(int)
    };

    struct ForwardIterator : public InputIterator
    {

    };

    struct BidirectionalIterator : public ForwardIterator
    {
        // operator--()
        // operator--(int)
    };

    struct RandomAccessIterator : public BidirectionalIterator
    {
        // operator+=()
        // operator-=()
        // operator+()
        // operator-()
        // operator[](int)
        // operator<()
        // operator>()
        // operator<=()
        // operator>=()
    };

    template <class Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::iterator_category    iterator_category;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
    };

    template <class T>
    struct iterator_traits<T*>
    {
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef ptrdiff_t                   difference_type;
        typedef T*                          pointer;
        typedef T&                          reference;
    };

    template <class T>
    struct iterator_traits<const T*>
    {
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef ptrdiff_t                   difference_type;
        typedef const T*                    pointer;
        typedef const T&                    reference;
    };

    template <class InputIterator>
    typename iterator_traits<InputIterator>::value_type
        sum_nonempty(InputIterator first, InputIterator last)
    {
        typename iterator_traits<InputIterator>::value_type result = *first++;
        for (; first != last; ++first)
            result += *first;
        return result;
    }

    template <class InputIterator, class T>
    typename iterator_traits<InputIterator>::difference_type
        count(InputIterator first, InputIterator last, const T& x)
    {
        typename iterator_traits<InputIterator>::difference_type n = 0;
        for (; first != last; ++first)
            ++n;
        return n;
    }

    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag :public input_iterator_tag {};
    struct bidirectional_iterator_tag :public forward_iterator_tag {};
    struct random_access_iterator_tag :public bidirectional_iterator_tag {};

    template <class InputIterator, class Distance>
    void advance(InputIterator& i, Distance n, input_iterator_tag)
    {
        for (; n > 0; --n, ++i) {}
    }

    template <class InputIterator, class Distance>
    void advance(InputIterator& i, Distance n, forward_iterator_tag)
    {
        advance(i, n, input_iterator_tag());
    }

    template <class InputIterator, class Distance>
    void advance(InputIterator& i, Distance n, bidirectional_iterator_tag)
    {
        if (n >= 0)
            for (; n > 0; --n, ++i) {}
        else
            for (; n < 0; ++n, --i) {}
    }

    template <class InputIterator, class Distance>
    void advance(InputIterator& i, Distance n, random_access_iterator_tag)
    {
        i += n;
    }

    template <class InputIterator, class Distance>
    inline void advance(InputIterator& i, Distance n)
    {
        advance(i, n, typename iterator_traits<i>::iterator_category());
    }

    template <
        class Category,
        class Value,
        class Distance = ptrdiff_t,
        class Pointer = Value*,
        class Reference = Value&>
        struct iterator
    {
        typedef Category    iterator_category;
        typedef Value       value_type;
        typedef Distance    difference_type;
        typedef Pointer     pointer;
        typedef Reference   reference;
    };

    template <class Container>
    struct back_insert_iterator : public iterator<output_iterator_tag, void, void, void, void>
    {
    protected:
        typedef back_insert_iterator<Container> Self;
        Container *container;
    public:
        typedef Container           container_type;
        typedef output_iterator_tag iterator_category;
        explicit back_insert_iterator(Container& x) :container(&x) {}
        Self& operator=(const Self& other) { container = other.container; return *this; }
        Self& operator=(const typename Container::value_type& val) { container->push_back(val); return *this; }
        Self& operator*() { return *this; }
        Self& operator++() { return *this; }
        Self operator++(int) { return *this; }
    };

    template <class Container>
    struct front_insert_iterator : public iterator<output_iterator_tag, void, void, void, void>
    {
    protected:
        typedef front_insert_iterator<Container> Self;
        Container *container;
    public:
        typedef Container           container_type;
        typedef output_iterator_tag iterator_category;
        explicit front_insert_iterator(Container& x) :container(&x) {}
        Self& operator=(const Self& other) { container = other.container; return *this; }
        Self& operator=(const typename Container::value_type& val) { container->push_front(val); return *this; }
        Self& operator*() { return *this; }
        Self& operator++() { return *this; }
        Self& operator++(int) { return *this; }
    };

    template <class ForwardIterator1, class ForwardIterator2>
    void iter_swap(ForwardIterator1 p, ForwardIterator2 q)
    {
        typename iterator_traits<ForwardIterator1>::value_type tmp = *p;
        *p = *q;
        *q = tmp;
    }

    template <class Node, class Reference, class Pointer>
    struct node_wrap_base : public iterator<forward_iterator_tag, Node, ptrdiff_t, Pointer, Reference>
    {
        typedef node_wrap_base<Node, Node&, Node*>              iterator;
        typedef node_wrap_base<Node, const Node&, const Node*>  const_iterator;
        Pointer ptr;

        node_wrap_base(Pointer p = 0) :ptr(p) {}
        node_wrap_base(const iterator& x) :ptr(x.ptr) {}

        Reference operator*() const { return *ptr; }
        Pointer operator->() const { return ptr; }

        void incr() { ptr = ptr->next; }

        bool operator==(const node_wrap_base& x) const { return ptr == x.ptr; }
        bool operator!=(const node_wrap_base& x) const { return ptr != x.ptr; }
    };

    template <class Node>
    struct node_wrap :public node_wrap_base<Node, Node&, Node*>
    {
        typedef node_wrap_base<Node, Node&, Node*>  Base;
        node_wrap(Node* p = 0) :Base(p) {}
        node_wrap(const node_wrap<Node>& x) :Base(x) {}
        node_wrap& operator++() { incr(); return *this; }
        node_wrap operator++(int) { node_wrap tmp = *this; incr(); return tmp; }
    };

    template <class Node>
    struct const_node_wrap :public node_wrap_base<Node, const Node&, const Node*>
    {
        typedef node_wrap_base<Node, const Node&, const Node*> Base;
        const_node_wrap(const Node* p = 0) :Base(p) {}
        const_node_wrap(const node_wrap<Node>& x) :Base(x) {}
        const_node_wrap& operator++() { incr(); return *this; }
        const_node_wrap operator++(int) { const_node_wrap tmp = *this; incr(); return tmp; }
    };

    template <class InputIterator, class Predicate>
    InputIterator find_if(InputIterator first, InputIterator last, Predicate pred)
    {
        while (first != last && !pred(*first))
            ++first;
        return first;
    }

    template <class ForwardIterator, class BinaryPredicate>
    ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate pred)
    {
        if (first == last)
            return last;
        ForwardIterator next = first;
        while (++next != last) {
            if (pred(*first, *next))
                return first;
            first = next;
        }
        return last;
    }

    template <class InputIterator, class OutputIterator, class UnaryFunction>
    OutputIterator transform(InputIterator first, InputIterator last, OutputIterator result, UnaryFunction f)
    {
        while (first != last)   *result++ = f(*first++);
        return result;
    }

    template<class _Container>
    auto inline begin(_Container& _Cont) -> decltype(_Cont.begin())
    {	// get beginning of sequence
        return (_Cont.begin());
    }

    template<class _Container>
    auto inline begin(const _Container& _Cont) -> decltype(_Cont.begin())
    {	// get beginning of sequence
        return (_Cont.begin());
    }

    template<class _Container>
    auto inline end(_Container& _Cont) -> decltype(_Cont.end())
    {	// get end of sequence
        return (_Cont.end());
    }

    template<class _Container>
    auto inline end(const _Container& _Cont) -> decltype(_Cont.end())
    {	// get end of sequence
        return (_Cont.end());
    }

    template<class _Ty,
        size_t _Size> 
        _Ty *begin(_Ty(&_Array)[_Size]) 
    {	// get beginning of array
        return (_Array);
    }

    template<class _Ty,
        size_t _Size> 
        _Ty *end(_Ty(&_Array)[_Size]) 
    {	// get end of array
        return (_Array + _Size);
    }

    template <class Arg, class Result>
    struct unary_function
    {
        typedef Arg     argument_type;
        typedef Result  result_type;
    };

    template <class Arg1, class Arg2, class Result>
    struct binary_function
    {
        typedef Arg1    first_argument_type;
        typedef Arg2    second_argument_type;
        typedef Result  result_type;
    };

    template <class Arg>
    struct equal_to :public binary_function<Arg, Arg, bool>
    {
        bool operator()(const Arg& x, const Arg& y) { return x == y; }
    };

    template <class Arg>
    struct plus :public binary_function<Arg, Arg, Arg>
    {
        Arg operator()(const Arg& x, const Arg& y) { return x + y; }
    };

    template <class Arg>
    struct minus :public binary_function<Arg, Arg, Arg>
    {
        Arg operator()(const Arg& x, const Arg& y) { return x - y; }
    };

    template <class Arg>
    struct multiplies :public binary_function<Arg, Arg, Arg>
    {
        Arg operator()(const Arg& x, const Arg& y) { return x * y; }
    };

    template <class Number>
    struct even :public unary_function<Number, bool>
    {
        bool operator()(Number x) const { return (x & 1) == 0; }
    };

    template <class AdaptablePredicate>
    class unary_negate
    {
    private:
        AdaptablePredicate pred;
    public:
        typedef typename AdaptablePredicate::argument_type  argument_type;
        typedef typename AdaptablePredicate::result_type    result_type;

        unary_negate(const AdaptablePredicate& x) : pred(x) {}
        bool operator()(const argument_type& x) const { return !pred(x); }
    };

    template <class AdaptablePredicate>
    inline unary_negate<AdaptablePredicate> not1(const AdaptablePredicate& pred)
    {
        return unary_negate<AdaptablePredicate>(pred);
    }

    template <class Arg, class Result>
    class pointer_to_unary_function : public unary_function<Arg, Result>
    {
    private:
        Result(*ptr)(Arg);
    public:
        pointer_to_unary_function() {}
        pointer_to_unary_function(Result(*x)(Arg)) : ptr(x) {}
        Result operator()(Arg x) const { return ptr(x); }
    };

    template <class Arg, class Result>
    inline pointer_to_unary_function<Arg, Result> ptr_fun(Result(*x)(Arg))
    {
        return pointer_to_unary_function<Arg, Result>(x);
    }

    template <class T>
    struct trivial_container
    {
        typedef T                   value_type;
        typedef value_type*         pointer;
        typedef const value_type*   const_pointer;
        typedef value_type&         reference;
        typedef const value_type&   const_reference;
        typedef value_type*         iterator;
        typedef const value_type*   const_iterator;
        typedef ptrdiff_t           difference_type;
        typedef size_t              size_type;
        const_iterator begin() const { return 0; }
        const_iterator end() const { return 0; }
        iterator begin() { return 0; }
        iterator end() { return 0; }
        size_type size() const { return 0; }
        bool empty() const { return true; }
        size_type max_size() const { return 0; }
        void swap(trivial_container&) {}
    };
};