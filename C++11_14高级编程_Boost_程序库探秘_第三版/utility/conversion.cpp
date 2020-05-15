// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/core/ignore_unused.hpp>
#include <boost/static_assert.hpp>

#include <boost/polymorphic_cast.hpp>
#include <boost/polymorphic_pointer_cast.hpp>
using namespace boost;

struct base1
{   virtual ~base1(){};};

struct base2
{   virtual ~base2(){};};

struct derived :public base1, public base2
{   virtual ~derived(){};};

struct derived2 :public base1
{   virtual ~derived2(){};};

///////////////////////////////////////

void case1()
{
    base1 *p = new derived;
    derived *pd = dynamic_cast<derived*>(p);
    base2 *pb2 = dynamic_cast<base2*>(p);

    string *ps = dynamic_cast<string*>(p);
    assert(!ps);

    ignore_unused(pd, pb2);

    try
    {
        string& s = dynamic_cast<string&>(*p);

        ignore_unused(s);
    }
    catch (bad_cast& e)
    {
        cout << e.what() << endl;
    }

}

///////////////////////////////////////

void case2()
{
    base1 *p = new derived;
    derived *pd = polymorphic_downcast<derived*>(p);

    //base2 *pb2 = polymorphic_downcast<base2*>(p);
    //string *ps = polymorphic_downcast<string*>(p);

    ignore_unused(p, pd);
}

///////////////////////////////////////

void case3()
{
    base1 *p = new derived;
    derived *pd = polymorphic_cast<derived*>(p);
    base2 *pb2 = polymorphic_cast<base2*>(p);


    ignore_unused(p, pd, pb2);
    try
    {
        derived2 *p2 = polymorphic_cast<derived2*>(p);
        string *ps = polymorphic_cast<string*>(p);

        ignore_unused(p2, ps);
    }
    catch (bad_cast& e)
    {
        cout << e.what() << endl;
    }

}

///////////////////////////////////////

/*
#define CAST_META_TYPE(a, b)   \
    typedef typename conditional<   \
        is_pointer<a>::value,   \
        typename remove_pointer<a>::type,   \
        typename remove_reference<a>::type  \
        >::type     b
*/

//template <class Target, class Source> inline
//Target my_polymorphic_downcast(Source* x )
//{
//    BOOST_STATIC_ASSERT(is_pointer<Target>::value);
//
//    CAST_META_TYPE(Target, T);
//    CAST_META_TYPE(Source, S);
//
//    BOOST_STATIC_ASSERT( is_polymorphic<T>::value);
//    BOOST_STATIC_ASSERT( is_polymorphic<S>::value);
//    BOOST_STATIC_ASSERT((is_base_of<S, T>::value));
//
//    return static_cast<Target>(x);
//};

namespace boost {

template <class Target, class Source> inline
Target polymorphic_downcast(Source& x)
{
    BOOST_STATIC_ASSERT(std::is_reference<Target>::value);

    typedef typename remove_reference<Target>::type T;
    typedef Source S;

    BOOST_STATIC_ASSERT( is_polymorphic<T>::value);
    BOOST_STATIC_ASSERT( is_polymorphic<S>::value);
    BOOST_STATIC_ASSERT((is_base_of<S, T>::value));

    return static_cast<Target>(x);
};

//template <class Target, class Source>
//inline Target my_polymorphic_cast(Source* x )
//{
//    BOOST_STATIC_ASSERT(is_pointer<Target>::value);
//
//    CAST_META_TYPE(Target, T);
//    CAST_META_TYPE(Source, S);
//
//    BOOST_STATIC_ASSERT( is_polymorphic<T>::value);
//    BOOST_STATIC_ASSERT( is_polymorphic<S>::value);
//
//    Target tmp = dynamic_cast<Target>(x);
//    if ( tmp == 0 ) throw std::bad_cast();
//    return tmp;
//};

template <class Target, class Source>
inline Target polymorphic_cast(Source& x)
{
    BOOST_STATIC_ASSERT(std::is_reference<Target>::value);

    typedef typename remove_reference<Target>::type T;
    typedef Source S;

    BOOST_STATIC_ASSERT( is_polymorphic<T>::value);
    BOOST_STATIC_ASSERT( is_polymorphic<S>::value);

    return dynamic_cast<Target>(x);
};

//#undef CAST_META_TYPE

}   // namespace boost

void case4()
{
    base1 *p = new derived;
    derived *pd = polymorphic_downcast<derived*>(p);
    derived &rd = polymorphic_downcast<derived&>(*p);

    pd = polymorphic_cast<derived*>(p);
    base2 &pb2 = polymorphic_cast<base2&>(rd);

    ignore_unused(pd, rd, pb2);
}

///////////////////////////////////////

int main()
{
    std::cout << "hello conversion" << std::endl;

    case1();
    case2();
    case3();
    case4();
}
