// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/core/enable_if.hpp>
using namespace boost;

///////////////////////////////////////

template<typename T>
//T print(T x , typename boost::enable_if<is_integral<T> >::type* =0)
//typename boost::enable_if<is_integral<T>, T >::type print(T x)
typename disable_if<is_class<T>, T >::type print(T x)
{
    cout << "int:" << x << endl;
    return x;
}

void case1()
{
    print(10);
    //print(10.0);
}

///////////////////////////////////////

template<typename T, typename Enable = void>
class demo_class
{   };

template<typename T>
class demo_class<T, typename boost::enable_if<is_arithmetic<T> >::type>
{   };


///////////////////////////////////////

int main()
{
    std::cout << "hello enable_if" << std::endl;

    case1();
}
