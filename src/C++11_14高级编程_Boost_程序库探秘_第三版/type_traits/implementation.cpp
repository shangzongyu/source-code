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
    assert((integral_constant<int, 10>::value == 10));

    static_assert(integral_constant<char, 0x30>::value == '0', "");

    static_assert(integral_constant<short, 100>::value == 100, "");

    static_assert(true_type::value == true, "");

    static_assert(mp_eval(false_type) == false, "");

}

///////////////////////////////////////

int main()
{
    std::cout << "hello type implementation" << std::endl;

    case1();
    //case2();
    //case3();
    //case4();
}
