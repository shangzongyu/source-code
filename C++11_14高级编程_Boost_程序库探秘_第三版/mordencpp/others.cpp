// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/core/ignore_unused.hpp>

///////////////////////////////////////

#if __cplusplus < 201103L
    #error "we need the latest C++ standard!"
#endif

///////////////////////////////////////

void case1()
{
    cout << "c++ : " << __cplusplus << endl;
}

///////////////////////////////////////

void case2()
{
    static_assert(sizeof(long long) >= 8, "long long is 64bit");

    long long m = -1000*1000;
    unsigned long long n = 1000*1000;

    auto a = 524287LL;
    auto b = 2147483647uLL;

    boost::ignore_unused(m, n, a, b);
}

///////////////////////////////////////

void case3()
{
    string s = R"(this is a "\string\" )";
    cout << s << endl;

    string reg = R"(^\d+\s\w+)";
    string reg2 = "^\\d+\\s\\w+";
    assert(reg == reg2);
    //cout << reg << endl;
    //cout << reg2 << endl;

    auto b = R"***(BioShock Infinity)***";
    auto d = R"====(Dark Souls)====";

    cout << b << "," << d << endl;
}

///////////////////////////////////////
#include <boost/type_index.hpp>

void case4()
{
    auto f = 3.14f;
    auto s = L"wide char";
    auto x = 0x100L;

    using namespace boost;
    cout << typeindex::type_id<decltype(f)>().pretty_name() << endl;
    cout << typeindex::type_id<decltype(s)>().pretty_name() << endl;
    cout << typeindex::type_id<decltype(x)>().pretty_name() << endl;
}

///////////////////////////////////////

#include <complex>
#include <boost/xpressive/xpressive.hpp>

long operator"" _kb(unsigned long long v)
{
    return v * 1024;
}

complex<double> operator"" _c(const char* s, size_t n)
{
    using namespace boost::xpressive;

    auto reg = cregex::compile(R"--(([0-9\.]+)\+([0-9\.]+)i)--");
    cmatch what;

    auto ok = regex_match(s, what, reg);
    assert(ok);

    return complex<double>(stod(what[1]), stod(what[2]));
}


void case5()
{
    auto x = 2_kb;
    assert(x == 2*1024);

    auto c = "1.414+1.414i"_c;
    cout << c << endl;
}

///////////////////////////////////////

int main()
{
    std::cout << "hello C++11/14 features" << std::endl;

    case1();
    case2();
    case3();
    case4();
    case5();
}
