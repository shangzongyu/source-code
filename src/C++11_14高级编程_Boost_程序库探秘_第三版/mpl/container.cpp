// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
//using namespace std;

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/int.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/clear.hpp>

using namespace boost;
using namespace boost::mpl;

///////////////////////////////////////

void case1()
{
    typedef mpl::vector<char, int , long,
        int_<8>, std::string> vec;

    assert((empty<vec>::value == false));
    assert((size<vec>::value == 5));

    assert((is_same<front<vec>::type, char>::value));
    assert((is_same<back<vec>::type, std::string>::value));
    assert((is_same<at_c<vec, 1>::type, int>::value));

    typedef push_front<vec, float>::type vec2;
    assert((size<vec2>::value == 6));
    assert((is_same<front<vec2>::type, float>::value));

    typedef clear<vec2>::type vec3;
    assert((empty<vec3>::value));

}

///////////////////////////////////////
#define BOOST_MPL_LIMIT_STRING_SIZE 24
#include <boost/mpl/string.hpp>

void case2()
{
    typedef mpl::string<'a','b','c'>    abc;
    typedef mpl::string<'Hell','o !!'> hello;
    //typedef mpl::string<'Hello !!'> hello2;
    //typedef mpl::string<"Hello !!"> hello3;

    boost::ignore_unused<abc>();

    assert((empty<hello>::value == false));
    assert((size<hello>::value == 8));

    assert((front<hello>::type::value == 'H'));
    assert((back<hello>::type::value == '!'));

    typedef push_back<hello, char_<'?'>>::type hello2;
    assert((c_str<hello2>::value ==
                std::string("Hello !!?") ));

}

///////////////////////////////////////
#include <boost/mpl/map.hpp>
#include <boost/mpl/count.hpp>

void case3()
{
    typedef mpl::map<
        mpl::pair<int, std::vector<int>>,
        mpl::pair<char,std::string>,
        mpl::pair<int_<3>, float[3]>
    > m;
    assert((empty<m>::value == false));
    assert((size<m>::value == 3));

    typedef front<m>::type p1;
    assert((is_same<first<p1>::type, int>::value));
    assert((is_same<p1::second,std::vector<int>>::value));

    assert((has_key<m, char>::value));
    assert((count<m, int_<0>>::value == 0));

    typedef at<m, char>::type mdata;
    assert((is_same<mdata, std::string>::value));

}

///////////////////////////////////////
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/distance.hpp>

void case4()
{
    typedef mpl::vector<char, int , long,
        int_<8>, std::string> vec;

    typedef begin<vec>::type i1;
    assert((is_same<deref<i1>::type, char>::value));

    typedef next<i1>::type i2;
    assert((is_same<deref<i2>::type, int>::value));
    assert((is_same<i1, prior<i2>::type>::value));

    typedef advance<i2, int_<4>>::type i3;
    assert((distance<i1, i3>::type::value == 5));
    assert((distance<i3, i1>::type::value == -5));
    assert((is_same<i3, mpl::end<vec>::type>::value));

    typedef insert<vec, i2, float>::type vec2;

    boost::ignore_unused<vec2>();
}
///////////////////////////////////////

int main()
{
    std::cout << "hello container" << std::endl;

    case1();
    case2();
    case3();
    case4();
}
