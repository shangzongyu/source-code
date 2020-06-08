// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
//using namespace std;

#include <boost/core/ignore_unused.hpp>
#include <boost/type_traits.hpp>

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/apply.hpp>

using namespace boost;
using namespace boost::mpl;

///////////////////////////////////////

void case1()
{
    typedef apply_wrap2<_1, int, char>::type t1;
    typedef apply<_3, int, char, float>::type t2;

    assert((is_same<t1, int>::value));
    assert((is_same<t2, float>::value));

}

///////////////////////////////////////

#include <boost/mpl/bind.hpp>

struct func1
{
    template<typename T1>
    struct apply
    {   typedef T1 type;};
};

void case2()
{
    typedef bind<func1, _1> f1;

    typedef apply<f1, int>::type data1;
    assert((is_same<data1, int>::value));

    typedef apply<bind<func1, float>>::type data2;
    assert((is_same<data2, float>::value));
}

///////////////////////////////////////

#include <boost/mpl/int.hpp>
#include <boost/mpl/arithmetic.hpp>
#include <boost/mpl/lambda.hpp>

void case3()
{
    typedef apply_wrap2<lambda<plus<_,_>>::type, int_<1>, int_<2>>::type data0;

    assert((data0::value == 3));

    typedef apply<plus<_,_>,
            int_<1>, int_<2>>::type data1;
    assert((data1::value == 3));

    typedef bind<lambda<plus<_,_>>::type, _1,_2> f1;
    typedef apply<f1, int_<1>, int_<2>>::type data2;
    assert((data2::value == 3));

}

///////////////////////////////////////

#include <boost/mpl/range_c.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/inserter.hpp>

void case4()
{
    typedef range_c<int, 1, 11> rc;
    typedef mpl::copy<rc,
            mpl::inserter<int_<0>, plus<_,_> >
                >::type sum;
    std::cout << sum::value;

}

///////////////////////////////////////
#include <boost/mpl/vector.hpp>
#include <boost/mpl/count_if.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/min_element.hpp>
#include <boost/mpl/max_element.hpp>

void case5()
{
    typedef mpl::vector<float, double,
        char, int, long> vec;

    assert((mpl::count_if<vec,
        is_float<_> >::value==2));
    assert((is_same<
            deref<mpl::find_if<vec,
            is_same<_, char>>::type>::type,
            char>::value));

    typedef lambda<less<sizeof_<_1>, sizeof_<_2>> > Comp;

    typedef deref<min_element<vec, Comp>::type>::type mint;
    assert((is_same<mint, char>::value));

    typedef deref<max_element<vec, Comp>::type>::type maxt;
    assert((is_same<maxt, double>::value));
}

///////////////////////////////////////

#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/copy_if.hpp>
#include <boost/mpl/replace_if.hpp>
#include <boost/mpl/remove_if.hpp>
#include <boost/mpl/sort.hpp>
#include <boost/mpl/unique.hpp>
#include <boost/mpl/modulus.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/greater.hpp>

void case6()
{
    typedef vector_c<int, 5,3,7,2,6,4,2> vec;

    typedef copy_if<vec,
        equal_to<modulus<_1, int_<2> > ,
                int_<0>> >::type vec2;

    typedef replace_if<vec2,
        equal_to<_1, int_<6> >, int_<10>>::type vec3;

    typedef remove_if<vec3,
        greater<_1, int_<5>>>::type vec4;

    typedef sort<vec4, less<_,_>>::type vec5;

    typedef unique<vec5, equal_to<_,_>>::type vec6;

    boost::ignore_unused<vec6>();
}


///////////////////////////////////////

int main()
{
    std::cout << "hello lambda" << std::endl;

    case1();
    case2();
    case3();
    case4();
    case5();
    case6();
}
