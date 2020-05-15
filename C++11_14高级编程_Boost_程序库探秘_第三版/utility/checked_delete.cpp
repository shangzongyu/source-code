// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/checked_delete.hpp>
using namespace boost;

///////////////////////////////////////

class demo_class;

void do_delete(demo_class* p)
//{   delete p;}
{   checked_delete(p);}

///////////////////////////////////////

void case1()
{
    auto p1 = new int(10);
    checked_delete(p1);

    auto p2 = new int[10];
    checked_array_delete(p2);

}

///////////////////////////////////////

class demo_class
{
public:
    ~demo_class()
    {   cout << "dtor exec." << endl;   }
};

void case2()
{
    auto p1 = new demo_class;

    //checked_delete(p1);
    checked_deleter<demo_class>()(p1);

    auto p2 = new demo_class[10];

    //checked_array_delete(p2);
    checked_array_deleter<demo_class>()(p2);

    cout << "try for_each" << endl;

    vector<demo_class*> v;
    v.push_back(new demo_class);
    v.push_back(new demo_class);

    for_each(v.begin(),v.end(), checked_deleter<demo_class>());

}

///////////////////////////////////////
struct my_checked_deleter
{
    typedef void result_type;

    template<class T>
    void operator()(T* x) const
    {
        boost::checked_delete(x);
    }
};

void case3()
{
    cout << "my_checked_deleter" << endl;

    auto p = new int(10);
    my_checked_deleter()(p);

    vector<int*> v;

    v.push_back(new int(10));
    for_each(v.begin(), v.end(),
            my_checked_deleter());

}

///////////////////////////////////////

void case4()
{
    cout << "incomplete type" << endl;

    auto p = new demo_class();
    //auto p = (demo_class*)(1996);

    do_delete(p);
}

///////////////////////////////////////

#include <boost/static_assert.hpp>

template<class Pointer> inline
void my_checked_delete(Pointer p)
{
    BOOST_STATIC_ASSERT(is_pointer<Pointer>::value);

    typedef typename remove_pointer<Pointer>::type T;
    BOOST_STATIC_ASSERT(is_object<T>::value);
    BOOST_STATIC_ASSERT(!is_array<T>::value);
    BOOST_STATIC_ASSERT(sizeof(T) >0 );

    delete p;
}

void case5()
{
    //auto p = new int[2][2];
    auto p = new int;
    my_checked_delete(p);
}

///////////////////////////////////////

int main()
{
    std::cout << "hello checked_delete" << std::endl;

    case1();
    case2();
    case3();
    case4();
    case5();
}
