// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

// for c++98
#include <boost/config.hpp>

///////////////////////////////////////

template<int N, int M>
struct meta_func
{
    static const int value = N + M;

    //static constexpr int value = N + M;

    // for c++98
    //BOOST_STATIC_CONSTANT(int, value = N + M);
};

template<typename T1, typename T2>
struct select1st
{
    typedef T1 type;
};

template<typename T1, typename T2>
struct forward : select1st<T2, T1>
{};

///////////////////////////////////////

#include "mp_utils.hpp"

mp_arglist<int L, int R>
mp_function static_min
{
    static const int value = (L < R) ? L : R;
};

///////////////////////////////////////
#include <boost/type_traits.hpp>

mp_arglist<mp_arg T>
mp_function demo_func
{
    mp_return(const T*);
};

mp_arglist<mp_arg T>
mp_function demo_func<T*>
{
    mp_return(const T);
};


int main()
{
    cout << "hello meta-programing" << endl;

    cout << meta_func<10, 10>::value << endl;

    //int i = 10, j = 10;
    //meta_func<i, j>::value;

    assert((static_min<10, 20>::value == 10));

    assert((is_same<mp_exec(demo_func<int>) , const int*>::value));
    assert((is_same<mp_exec(demo_func<int*>), const int >::value));

}
