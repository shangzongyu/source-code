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
    mp_data mp_exec(add_const<int>) mdata1;
    assert((is_const<mdata1>::value));
    assert((is_same<mdata1, int const>::value));

    mp_data mp_exec(add_pointer<double>) mdata2;
    assert((is_pointer<mdata2>::value));
    assert((is_same<mdata2, double*>::value));

    mp_data mp_exec(add_lvalue_reference<mdata2>) mdata3;
    assert((is_lvalue_reference<mdata3>::value));
    assert((is_same<mdata3, double*&>::value));

    mp_data mp_exec(add_lvalue_reference<void>) mdata4;
    assert((is_void<mdata4>::value));

}

///////////////////////////////////////

void case2()
{
    mp_data int const **& mdata1;

    mp_data mp_exec(remove_pointer<mdata1>) mdata2;
    assert((is_same<mdata2, mdata1>::value));

    mp_data mp_exec(remove_reference<mdata2>) mdata3;
    assert((is_pointer<mdata3>::value));
    assert((is_same<mdata3, int const**>::value));

    mp_data mp_exec(remove_pointer<
            mp_exec(remove_pointer<mdata3>)>) mdata4;

    assert((is_const<mdata4>::value));
    assert((is_integral<mdata4>::value));
    assert((is_same<mdata4, int const>::value));

    mp_data mp_exec(remove_const<mdata4>) mdata5;
    assert((is_same<mdata5, int>::value));

}

///////////////////////////////////////

void case3()
{
    mp_data short const mdata1;

    mp_data mp_exec(make_signed<mdata1>) mdata2;
    assert((is_const<mdata2>::value));
    assert((is_signed<mdata2>::value));

    assert((is_same<mdata2, signed short const>::value));

    mp_data mp_exec(make_unsigned<mdata2>) mdata3;
    assert((is_same<mdata3, unsigned short const>::value));
}

///////////////////////////////////////

void case4()
{
    //mp_data int(mdata1)[5][7][9] ;
    using mdata1 = int[5][7][9];

    mp_data mp_exec(remove_extent<mdata1>) mdata2;
    assert((is_same<mdata2, int[7][9]>::value));

    mp_data mp_exec(remove_all_extents<mdata1>) mdata4;
    assert((is_same<mdata4, int>::value));

}

///////////////////////////////////////
void case5()
{
    typedef common_type<int, char>::type mdata1;
    assert((is_same<mdata1, int>::value));

    typedef common_type<int, double>::type mdata2;
    assert((is_same<mdata2, double>::value));

    //typedef common_type<int, std::string>::type mdata3;

}

///////////////////////////////////////

int main()
{
    std::cout << "hello type modifications" << std::endl;

    case1();
    case2();
    case3();
    case4();
    case5();
}
