// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/mpl/if.hpp>
using namespace boost;
using namespace boost::mpl;

///////////////////////////////////////
#include <boost/type_traits.hpp>

void case1()
{
    typedef if_c<true, int, long>::type mdata1;
    assert((std::is_same<mdata1, int>::value));

    typedef if_<false_, float, double>::type mdata2;
    assert((std::is_same<mdata2, double>::value));

    typedef if_<std::is_integral<mdata2>,
        integral_promotion<mdata2>::type,
        floating_point_promotion<mdata2>::type
    >::type mdata3;
    assert((std::is_same<mdata3, double>::value));

}

///////////////////////////////////////

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

void case2()
{
    typedef eval_if_c<true,
        identity<int>, identity<long>>::type mdata1;
    assert((std::is_same<mdata1, int>::value));

    typedef eval_if<false_,
        identity<float>, identity<double>>::type mdata2;
    assert((std::is_same<mdata2, double>::value));

    typedef eval_if<std::is_integral<mdata2>,
        integral_promotion<mdata2>,
        floating_point_promotion<mdata2>
    >::type mdata3;
    assert((std::is_same<mdata3, double>::value));

}

///////////////////////////////////////

int main()
{
    std::cout << "hello if" << std::endl;

    case1();
    case2();
}
