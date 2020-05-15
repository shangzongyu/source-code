// Copyright (c) 2016
// Author: Chrono Law
#include <memory>
#include <std.hpp>
using namespace std;

///////////////////////////////////////

#include <boost/pointee.hpp>
//using namespace boost;

void case1()
{
    assert((is_same<boost::pointee<int*>::type, int>::value));
    assert((is_same<boost::pointee<unique_ptr<int> >::type, int>::value));
    assert((is_same<typename boost::pointee<string::iterator>::type, char>::value));

    typedef shared_ptr<int> P;
    P p(new int(10));
    boost::pointee<P>::type v = *p;
    assert(v == 10);
}

///////////////////////////////////////

#include <boost/indirect_reference.hpp>

void case2()
{
    assert((is_same<boost::indirect_reference<int*>::type, int&>::value));
    assert((is_same<boost::indirect_reference<unique_ptr<int> >::type, int&>::value));
    assert((is_same<boost::indirect_reference<string::iterator>::type, char&>::value));

}

///////////////////////////////////////

#include <boost/pointer_to_other.hpp>
#include <boost/smart_ptr.hpp>

void case3()
{
    assert((is_same<int*, 
        boost::pointer_to_other<void*, int>::type>::value));
    assert((is_same<string*,
        boost::pointer_to_other<void*, string>::type>::value));

    assert((is_same<boost::scoped_ptr<int>,
        boost::pointer_to_other<boost::scoped_ptr<float>, int>::type>::value));
    assert((is_same<shared_ptr<int>,
        boost::pointer_to_other<shared_ptr<string>, int>::type>::value));

    assert((!is_same<unique_ptr<int>,
        boost::pointer_to_other<unique_ptr<char>, int>::type>::value));

    assert((is_same<unique_ptr<int>,
                       boost::pointer_to_other<unique_ptr<
                       char,default_delete<int>>,int>::type>::value));

}

///////////////////////////////////////

#include <boost/optional.hpp>
#include <boost/utility/compare_pointees.hpp>

void case4()
{
    boost::scoped_ptr<int> p1(new int(10));
    boost::scoped_ptr<int> p2(new int(20));

    assert(!boost::equal_pointees(p1, p2));
    assert(boost::less_pointees(p1, p2));

    p2.reset();
    assert(!boost::less_pointees(p1, p2));

    boost::optional<string> op1, op2;

    assert(boost::equal_pointees(op1, op2));
    op2 = "hello";
    assert(boost::less_pointees(op1, op2));
}

///////////////////////////////////////

void case5()
{
    assert((is_same<pointer_traits<int*>::pointer, int*>::value));
    assert((is_same<pointer_traits<int*>::element_type, int>::value));
    assert((is_same<pointer_traits<int*>::rebind<char>,
                 boost::pointer_to_other<int*, char>::type >::value));

    typedef shared_ptr<std::string> sptr;
    assert((is_same<pointer_traits<sptr>::element_type,
                    boost::pointee<sptr>::type>::value));

    assert((is_same<pointer_traits<sptr>::difference_type, ptrdiff_t>::value));
    assert((is_same<pointer_traits<sptr>::rebind<char>,
                 boost::pointer_to_other<sptr, char>::type >::value));

    typedef unique_ptr<char> char_ptr;
    typedef unique_ptr<int> int_ptr;
    typedef std::pointer_traits<char_ptr>::rebind<int> new_ptr;
    assert((!std::is_same<int_ptr, new_ptr>::value));

}

///////////////////////////////////////

int main()
{
    std::cout << "hello pointee" << std::endl;

    case1();
    case2();
    case3();
    case4();
    case5();
}
