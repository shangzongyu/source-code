// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#define BOOST_THEAD_VERSION 4
#include <boost/thread.hpp>

#include <boost/core/ignore_unused.hpp>

///////////////////////////////////////

extern int x;
static int y = 0;
thread_local int z = 0;

//void test()
//{
//    ++y;
//    ++z;
//
//    cout << y << "," << z << endl;
//}

void case1()
{
    using namespace boost;

    auto f = [&](){
        ++y; ++z;
        cout << y << "," << z << endl;
        };

    thread t1(f);
    thread t2(f);

    t1.join();
    t2.join();

    cout << y << "," << z << endl;
}

///////////////////////////////////////

class demo final
{
public:
    demo()
    {
        cout << "demo" << endl;
    }
    ~demo()
    {
        cout << "~demo" << endl;
    }
};

void test_obj()
{
    cout << "begin func" << endl;
    thread_local demo obj;
    boost::ignore_unused(obj);
    cout << "end func" << endl;
}

void case2()
{
    using namespace boost;

    auto f = [&](){
        cout << "begin thread" << endl;
        test_obj();
        cout << "end thread" << endl;
        };

    thread t1(f);
    thread t2(f);

    t1.join();
    t2.join();

    cout << "end case" << endl;
}

///////////////////////////////////////

class demo2 final
{
public:
    demo2()
    {
        cout << "demo2" << endl;
    }
    ~demo2()
    {
        cout << "~demo2" << endl;
    }
};


demo& test_static()
{
    thread_local demo obj;
    demo2 obj2;

    return obj;
}

void case3()
{
    using namespace boost;

    auto f = [&](){
        auto& obj = test_static();
        cout << "obj = " << &obj << endl;
        };

    thread t1(f);

    t1.join();
}

///////////////////////////////////////

int main()
{
    std::cout << "hello C++11/14 thread" << std::endl;

    case1();
    case2();
    case3();
}

