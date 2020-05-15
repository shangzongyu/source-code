// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
//using namespace std;

#include <boost/type_traits.hpp>
using namespace boost;

#include "../meta/mp_utils.hpp"

///////////////////////////////////////

void case1()
{
    typedef const volatile int cv_int;
    assert(mp_eval(is_const<cv_int>));
    assert(mp_eval(is_volatile<cv_int>));
    assert(mp_eval(is_signed<cv_int>));

    assert(mp_eval(rank<int[2][3]>) == 2);

    assert((extent<int[2][3], 1>::value == 3));
}

///////////////////////////////////////

void case2()
{
    assert(!mp_eval(is_pod<std::string>));
    assert(mp_eval(is_empty<std::plus<int> >));
    assert(mp_eval(is_polymorphic<std::iostream>));

    struct x final {};
    assert(mp_eval(!is_abstract<x>));
    assert(mp_eval(is_final<x>));
}

///////////////////////////////////////

void case3()
{
    assert(mp_eval(has_greater<int>));
    assert(mp_eval(has_less<int>));
    assert(mp_eval(has_equal_to<int>));

    assert(mp_eval(has_greater<std::string>));
    assert(mp_eval(has_equal_to<std::string>));
    assert(mp_eval(has_plus<std::string>));
    assert(!mp_eval(has_minus<std::string>));

    assert(mp_eval(has_pre_increment<std::string::iterator>));
}

///////////////////////////////////////

int main()
{
    std::cout << "hello type properties" << std::endl;

    case1();
    case2();
    case3();
}
