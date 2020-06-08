// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/core/ignore_unused.hpp>

///////////////////////////////////////

void case1()
{
    //long x = 0L;
    //const char* s = "zelda";
    auto x = 0L;
    auto s = "zelda";

    map<string, string> m;
    //map<string, string>::iterator iter = m.begin();
    auto iter = m.begin();

    auto f = bind1st(std::less<int>(), 2);

    boost::ignore_unused(x, s, iter, f);
}

///////////////////////////////////////

namespace temp {

auto func(int x) -> decltype(x)
{
    return x*x;
}
}

void case2()
{
    int x = 0;
    const long y = 100;
    volatile string s("one punch");

    auto a1 = ++x;
    auto& a2 = x;
    auto a3 = y*y;
    auto& a4 = y;
    auto a5 = std::move(y);
    auto&& a6 = std::move(y);
    const auto a7 = x+x;
    auto* a8 = &y;
    auto&& a9 = s;
    //auto a10;

    static_assert(is_same<decltype(a1), int>::value, "");
    static_assert(is_same<decltype(a2), int&>::value, "");
    static_assert(is_same<decltype(a3), long>::value, "");
    static_assert(is_same<decltype(a4), const long&>::value, "");
    static_assert(is_same<decltype(a5), long>::value, "");
    static_assert(is_same<decltype(a6), const long&&>::value, "");
    static_assert(is_same<decltype(a7), const int>::value, "");
    static_assert(is_same<decltype(a8), const long*>::value, "");
    static_assert(is_same<decltype(a9), volatile string&>::value, "");

    using namespace temp;
    static_assert(is_same<decltype(func(3)), int>::value, "");

    auto&& a11 = y;
    static_assert(is_same<decltype(a11), const long&>::value, "");
}

///////////////////////////////////////

void case3()
{
    int x = 0;
    const long y = 100;

    decltype(x) d1 = x;
    decltype(x)& d2 = x;
    decltype(&x) d3 = &x;
    decltype(x+y) d4 = x + y;
    decltype(y)& d5 = y;

    static_assert(is_same<decltype(d1), int>::value, "");
    static_assert(is_same<decltype(d2), int&>::value, "");
    static_assert(is_same<decltype(d3), int*>::value, "");
    static_assert(is_same<decltype(d4), long>::value, "");
    static_assert(is_same<decltype(d5), const long&>::value, "");
}

///////////////////////////////////////
decltype(std::less<int>()) functor;

decltype(0.0f) func(decltype(0L) x)
{
    return x*x;
}

typedef decltype(func)* func_ptr;

template<typename T>
class demo {};

void case4()
{
    vector<int> v;

    decltype(v)::iterator iter;
    demo<decltype(v)> obj;

    boost::ignore_unused(v, iter, obj);
}

///////////////////////////////////////

void case5()
{
    int x = 0;
    const volatile int y = 0;

    decltype(x) d1 = x;
    decltype((x)) d2 = x;
    decltype(y) d3 = y;
    decltype((y)) d4 = y;

    static_assert(is_same<decltype(d1), int>::value, "");
    static_assert(is_same<decltype(d2), int&>::value, "");
    static_assert(is_same<decltype(d3), const volatile int>::value, "");
    static_assert(is_same<decltype(d4), const volatile int&>::value, "");

    struct demo
    {
        int x = 0;
    };

    volatile auto *p = new demo;

    decltype(p->x) d5 = 42;
    decltype((p->x)) d6 = p->x;
    //decltype(p->x)& d7 = p->x;

    static_assert(is_same<decltype(d5), int>::value, "");
    static_assert(is_same<decltype(d6), volatile int&>::value, "");
}

///////////////////////////////////////

//auto func(int x) -> type {}

template<typename T, typename U>
auto calc(T t, U u) -> decltype(t + u)
//typename std::common_type<T,U>::type calc(T t, U u)
{
    return t+u;
}

void case6()
{
    auto v = calc(1L, 0.618);

    static_assert(is_same<decltype(v), double>::value, "");
}

///////////////////////////////////////

int main()
{
    std::cout << "hello C++11/14 auto" << std::endl;

    case1();
    case2();
    case3();
    case4();
    case5();
    case6();
}

