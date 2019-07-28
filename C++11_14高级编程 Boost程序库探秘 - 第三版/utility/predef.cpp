// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/predef.h>

///////////////////////////////////////

void case1()
{
    cout << __cplusplus << endl;
    cout << BOOST_LANG_STDCPP << endl;
}

///////////////////////////////////////

void case2()
{
    cout << BOOST_OS_LINUX << endl;
    cout << BOOST_OS_MACOS << endl;
    cout << BOOST_OS_BSD << endl;
    cout << BOOST_OS_IOS << endl;
}

///////////////////////////////////////

int main()
{
    std::cout << "hello predef" << std::endl;

    case1();
    case2();
}
