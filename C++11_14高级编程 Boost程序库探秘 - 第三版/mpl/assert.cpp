// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
//using namespace std;

#include <boost/core/ignore_unused.hpp>
#include <boost/type_traits.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/equal_to.hpp>

using namespace boost;
using namespace boost::mpl;

///////////////////////////////////////

#include <boost/mpl/assert.hpp>

void case1()
{
    typedef mpl::vector<int, char> vec;

    BOOST_MPL_ASSERT((is_same<int,
                front<vec>::type> ));

    //BOOST_MPL_ASSERT((equal_to<
    //            size<vec>::type, int_<3>>));

}

///////////////////////////////////////
template<typename T>
struct my_operation
{
    BOOST_MPL_ASSERT_NOT((is_integral<T>));
    BOOST_MPL_ASSERT((
            is_integral<typename T::value_type>));

    typedef typename next<T>::type type;
};

void case2()
{
    typedef my_operation<int_<3>>::type t;
    //typedef my_operation<int>::type error;

    boost::ignore_unused<t>();

    BOOST_MPL_ASSERT_RELATION(int_<5>::value, >, 0);
    //BOOST_MPL_ASSERT_RELATION(sizeof(int), >, sizeof(long));
}


///////////////////////////////////////

template<typename T>
struct my_operation2
{
    BOOST_MPL_ASSERT_MSG(!is_pod<T>::value,
        IS_POD_ERROR, (T));
};

void case3()
{
    //BOOST_MPL_ASSERT_MSG(1>2, DEMO_MESSAGE, ());
    //my_operation2<int>::type;
}

///////////////////////////////////////
#include <boost/mpl/print.hpp>
#include <boost/mpl/transform.hpp>

void case4()
{
    typedef mpl::print<int>::type x;
    typedef mpl::vector<char, int_<5>, float> vec;
    typedef transform<vec, print<_>>::type none;

    boost::ignore_unused<x, none>();
}

///////////////////////////////////////

int main()
{
    std::cout << "hello debug" << std::endl;

    case1();
    case2();
    case3();
    //case4();
}
