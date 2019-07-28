// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
//using namespace std;

#include <boost/type_traits.hpp>
using namespace boost;

#include "../meta/mp_utils.hpp"

///////////////////////////////////////

mp_arglist<mp_arg T>
mp_function demo_func:
    conditional<
        is_pointer<T>::value,
        typename add_const<
            typename remove_pointer<T>::type
            >::type,
        typename add_pointer<
            typename add_const<T>::type
            >::type
    >{};

///////////////////////////////////////

#include <boost/mpl/eval_if.hpp>

mp_arglist<mp_arg T>
mp_function demo_func2:
    mpl::eval_if<
    is_pointer<T>,
        add_const<
            typename remove_pointer<T>::type
            >,
        add_pointer<
            typename add_const<T>::type
            >
    >{};


///////////////////////////////////////

int main()
{
    std::cout << "hello type examples" << std::endl;
}
