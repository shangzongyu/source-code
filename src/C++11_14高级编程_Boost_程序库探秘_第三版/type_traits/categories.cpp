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
    assert(mp_eval(is_integral<const char>));
    assert(mp_eval(is_integral<unsigned long>));
    assert(mp_eval(is_integral<long long>));
    assert(!mp_eval(is_integral<int*>));

    assert(mp_eval(is_floating_point<double>));
    assert(mp_eval(is_floating_point<float>));
    assert(!mp_eval(is_floating_point<int>));

    assert(mp_eval(is_void<void>));
    assert(!mp_eval(is_void<void*>));

    // c++14
    //assert(mp_eval(is_null_pointer<int>));
}

///////////////////////////////////////

void case2()
{
    assert(mp_eval(is_array<double[]>));
    assert(mp_eval(is_array<int[2][3]>));

    assert(mp_eval(is_class<struct dummy>));
    assert(mp_eval(is_class<std::vector<int> >));

    assert(mp_eval(is_pointer<int*>));
    assert(mp_eval(is_pointer<int(*)(int)>));

    assert(mp_eval(is_function<void(int,double)>));

    typedef float& float_ref;
    assert(mp_eval(is_lvalue_reference<float_ref>));
    assert(mp_eval(is_lvalue_reference<float_ref&>));
    assert(mp_eval(is_lvalue_reference<float_ref&&>));
    assert(mp_eval(is_rvalue_reference<float&&>));

}

///////////////////////////////////////

struct dummy
{
    int x;
    double y;
    void func(){}
};

void case3()
{
    assert(mp_eval(is_member_object_pointer<int dummy::*>));
    assert(mp_eval(is_member_object_pointer<double dummy::*>));
    assert(mp_eval(is_member_function_pointer<void(dummy::*)()>));
}

///////////////////////////////////////

void case4()
{
    assert(mp_eval(is_reference<float&>));
    assert(mp_eval(is_reference<float&&>));
    assert(mp_eval(is_reference<std::deque<int> const&>));

    assert(mp_eval(is_arithmetic<char>) );
    assert(mp_eval(is_arithmetic<float volatile>));

    assert(!mp_eval(is_arithmetic<void const>));
    assert(mp_eval(is_fundamental<void const>));

    assert(mp_eval(is_member_pointer<int(dummy::*)>));

    assert(mp_eval(is_compound<std::string>));
    assert(mp_eval(is_object<std::string>));

    assert(mp_eval(is_scalar<int>));
    assert(!mp_eval(is_scalar<std::vector<int> >));

}

///////////////////////////////////////

int main()
{
    std::cout << "hello type categories" << std::endl;

    case1();
    case2();
    case3();
    case4();
}
