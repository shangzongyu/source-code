// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/call_traits.hpp>
using namespace boost;

///////////////////////////////////////

typedef call_traits<string> str_traits;

str_traits::value_type
scat(str_traits::param_type s1,
     str_traits::param_type s2)
{
    assert(is_reference<str_traits::param_type>::value);

    assert((is_same<str_traits::param_type,
                const string&>::value));

    return s1 + s2;
}

///////////////////////////////////////

template<typename T>
class demo_class
{
public:
    typedef typename call_traits<T>::value_type v_type;
    typedef typename call_traits<T>::param_type p_type;
    typedef typename call_traits<T>::reference  r_type;
    typedef typename call_traits<T>::const_reference cr_type;
private:
    v_type v;
public:
    demo_class(p_type p): v(p){}

    v_type value()
    {   return v;   }

    r_type get()
    {   return v;   }
};

void case1()
{
    int a[3] = {1,2,3};
    demo_class<int[3]> di(a);
    assert(di.value()[0] == 1);

    char c = 'A';
    demo_class<char&> dc(c);
    assert(dc.get() == c);

}

///////////////////////////////////////

int main()
{
    std::cout << "hello call_traits" << std::endl;

    case1();
}
