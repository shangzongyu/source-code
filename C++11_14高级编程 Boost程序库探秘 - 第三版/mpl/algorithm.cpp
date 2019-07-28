// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
//using namespace std;

#include <boost/mpl/for_each.hpp>
#include <boost/mpl/tag.hpp>
#include <boost/type_index.hpp>

#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/string.hpp>
#include <boost/mpl/copy.hpp>

using namespace boost;
using namespace boost::mpl;

///////////////////////////////////////

#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/front_inserter.hpp>
#include <boost/mpl/copy.hpp>

void case1()
{
    typedef mpl::vector<char, int , long> vec;

    typedef copy<vec,
        mpl::back_inserter<vec>>::type vec2;
    assert((size<vec2>::value == 6));

    typedef mpl::string<> str1;
    typedef copy<
        mpl::string<'time'>,
        mpl::front_inserter<str1>>::type str2;
    std::cout << c_str<str2>::value << std::endl;

}

///////////////////////////////////////

#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/count.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/size.hpp>

void case2()
{
    typedef range_c<int, 0, 10> rc;
    assert((size<rc>::value == 10));

    #define INTV(n) integral_c<rc::value_type, n>

    assert((deref<
        find<rc, INTV(0)>::type
        >::type::value == 0));

    assert((contains<rc, INTV(9)>::value));
    assert((!contains<rc, INTV(10)>::value));

    assert((count<rc, INTV(5)>::value == 1));
    assert((count<rc, INTV(-5)>::value == 0));

    typedef vector_c<int, 0,1,2,3,4,5,6,7,8,9> vec;
    assert((equal<rc, vec>::value));
    assert((!is_same<rc, vec>::value));

}

///////////////////////////////////////
#include <boost/mpl/reverse.hpp>
#include <boost/mpl/replace.hpp>
#include <boost/mpl/remove.hpp>

void case3()
{
    typedef mpl::vector<char, short, int, long> vec;
    typedef replace<vec,
        int, char>::type vec2;

    assert((count<vec2, char>::value == 2));
    assert((is_same<deref<
                advance<begin<vec2>::type, int_<2>>::type>::type, 
                char>::value));

    typedef mpl::remove<vec2, short>::type vec3;
    assert((!contains<vec3, short>::value));

    assert((equal<
        reverse<vec3>::type,
        mpl::vector<long, char, char>
        >::value));

}

///////////////////////////////////////

struct mpl_func1
{
    template<typename T>
    void operator()(T t)
    {   std::cout << typeindex::type_id<T>().pretty_name() << std::endl;   }
    //{   std::cout << typeid(t).name() << std::endl;   }
};

struct mpl_func2
{
    template<typename T>
    void operator()(T t)
    {
        if (is_same<typename tag<T>::type, integral_c_tag>::value)
        {   std::cout << t << ',';}
    }
};

void case4()
{
    typedef range_c<int, 0, 5> rc;

    typedef mpl::vector<> vec;

    typedef mpl::copy<rc,
        mpl::back_inserter<vec>>::type vec2;

    typedef push_front<vec2, float>::type vec3;

    mpl::for_each<vec3>(mpl_func1());

    std::cout << std::endl;

    mpl::for_each<vec3>(mpl_func2());
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
