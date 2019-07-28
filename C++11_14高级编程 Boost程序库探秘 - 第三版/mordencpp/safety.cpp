// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/core/ignore_unused.hpp>

///////////////////////////////////////

void func() noexcept
{}

///////////////////////////////////////

namespace {
    int x = 0;
}

inline namespace temp{
    int xx = 0;
}

namespace release {
    namespace v001 {
        void func() {}
    }
    inline namespace v002 {
        void func() {}
    }
}

void case1()
{
    assert(x == 0);
    assert(xx == 0);

    release::func();
}

///////////////////////////////////////

enum class color : char {
    red = 1,
    green = 2,
    blue = 3
};

void case2()
{
    //int red = 1;
    //assert(red == green -1);
    auto x = color::red;
    //auto y = red;
    //auto z = color::red + 1;

    boost::ignore_unused(x);
}

///////////////////////////////////////


void case3()
{
    [[deprecated]] int x = 0;

    class [[deprecated]] demo {};

    boost::ignore_unused(x);
}

///////////////////////////////////////

int main()
{
    std::cout << "hello C++11/14 safety features" << std::endl;

    case1();
    case2();
    case3();
}

