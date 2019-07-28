// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

//#include <boost/type_traits.hpp>

#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/next_prior.hpp>

using namespace boost;
using namespace boost::mpl;

///////////////////////////////////////


void case1()
{
    typedef int_<2> i2;
    typedef integral_c<short, 2> s2;

    assert(i2::value == 2);
    assert(i2::value == s2::value);

    assert((is_same<i2::type, i2>::value));
    assert((is_same<s2::value_type, short>::value));

    assert(i2::next::value == 3);
    assert(prior<s2>::type::value == 1);

    i2 two1;
    s2 two2;

    int i = two1 + two2;
    assert(i == int_<4>());

}

///////////////////////////////////////

#include <boost/mpl/bool.hpp>

void case2()
{
    assert(true_::value == true);
    assert(false_::value == false);

    assert((is_same<true_::type, bool_<true> >::value));
    assert((is_same<false_::value_type, bool>::value));

    //next<true_>::type;

}

///////////////////////////////////////

#include <boost/mpl/arithmetic.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/mpl/comparison.hpp>

void case3()
{
    typedef int_<2> i2;
    typedef int_<5> i5;
    typedef int_<7> i7;

    assert((boost::mpl::plus<i2, i5, i7>::type::value == 14));
    assert((boost::mpl::equal_to<boost::mpl::minus<i7, i5>::type, i2>::type::value));

    assert((boost::mpl::less<i2, i7>::type::value));
    assert((is_same<boost::mpl::greater<i5, i2>::type, true_>::value));

    assert((not_<and_<true_, false_>::type>::type::value));
    assert((or_<true_, false_>::type()));

}

///////////////////////////////////////

#include <boost/mpl/char.hpp>
#include <boost/mpl/long.hpp>

void case4()
{
    typedef boost::mpl::plus<int_<1>, char_<2>, long_<3>>::type
            result;

    assert(!(is_same<result, long_<6>>::type::value));

    assert((is_same<result, integral_c<long, 6>>::type::value));

}

///////////////////////////////////////

int main()
{
    std::cout << "hello integral" << std::endl;

    case1();
    case2();
    case3();
}
