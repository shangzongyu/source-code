// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/core/ignore_unused.hpp>

///////////////////////////////////////

void case1()
{
    using int64 = long;
    using llong = long long;

    //typedef long int64;

    boost::ignore_unused<int64, llong>();
}

///////////////////////////////////////

template<typename T, typename U>
class demo final {};

template<typename T>
using demo_long = demo<T, long>;

template<typename T>
using int_map = std::map<int, T>;

void case2()
{
    int_map<string> m;
    demo<char, int> d1;
    demo_long<char> d2;

    boost::ignore_unused(m, d1, d2);
}

///////////////////////////////////////

void case3()
{
    static_assert(sizeof(int)==4, "int must be 32bit");
    static_assert(sizeof(long)>=8, "need 64bit!");
}

///////////////////////////////////////

constexpr long giga()
{
    return 1000*1000*1000;
}

void case4()
{
    const int k = 1024;
    constexpr int kk = 1024;

    static_assert(kk == 1024, "");

    boost::ignore_unused(k);
}

///////////////////////////////////////

template<typename K, typename V>
using x = std::map<K, V>;

template<typename ... T>
class variadic_class
{
    using type = x<T...>;
};

template<typename ... Args>
void variadic_func(Args... args)
{
    cout << sizeof...(Args) << endl;
}

template<typename ... Args>
int print( const char *format, const Args& ... args)
//int print( const char *format, Args&& ... args)
{
    return printf(format, args...);
    //return printf(format, std::forward<Args>(args)...);
}

void case5()
{
    variadic_func(1,2,3);
    print("hello %s %s\n", "variadic", "template");
}

///////////////////////////////////////

int main()
{
    std::cout << "hello C++11/14 generic" << std::endl;

    case1();
    case2();
    case3();
    case4();
    case5();
}

