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
    mp_data void(mdata1)(int, std::string);
    assert((is_function<mdata1>::value));

    const size_t n = function_traits<mdata1>::arity;
    assert((n == 2));

    mp_data function_traits<mdata1>::result_type rtype;
    assert((is_void<rtype>::value));

    mp_data function_traits<mdata1>::arg2_type a2type;
    assert((is_same<a2type, std::string>::value));

}

///////////////////////////////////////

int main()
{
    std::cout << "hello function_traits" << std::endl;

    case1();
}
