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
    mp_data int     meta_data1;
    mp_data short   meta_data2;

    assert((is_same<int, meta_data1>::value));
    assert((is_convertible<meta_data2, int>::value));

    assert((is_base_of<std::string, std::string>::value));
    assert((is_base_of<std::ios_base, std::ostream>::value));

    assert((!is_virtual_base_of<std::ios_base, std::ostream>::value));
    assert((is_virtual_base_of<std::basic_ios<char>, std::ostream>::value));
}

///////////////////////////////////////

int main()
{
    std::cout << "hello type relationships" << std::endl;

    case1();
}
