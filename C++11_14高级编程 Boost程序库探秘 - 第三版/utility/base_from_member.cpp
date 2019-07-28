// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#define BOOST_BASE_FROM_MEMBER_MAX_ARITY  2
#include <boost/utility/base_from_member.hpp>
using namespace boost;

///////////////////////////////////////

class base
{
public:
    base(complex<int> c)
    {
        cout << "base ctor" << endl;
        cout << c << endl;
    }
};

class base2
{
public:
    base2(string &x, string &y)
    {
        cout << "base2 ctor" << endl;
        cout << x <<  y << endl;
    }
};

///////////////////////////////////////

//class derived:public base
//{
//    complex<int> c;
//public:
//    derived(int a, int b):c(a, b),base(c)
//    {
//        cout << "derived ctor" << endl;
//        cout << c << endl;
//    }
//};

namespace ns1 {

class derived:
    private base_from_member<complex<int> >,
    public base
{
    //complex<int> c;
    typedef base_from_member<complex<int> > pbase_type;
public:
    derived(int a, int b):pbase_type(a, b),base(member)
    {
        cout << "derived ctor" << endl;
        cout << member << endl;
    }
};

}

void case1()
{
    ns1::derived d(10, 20);
}

///////////////////////////////////////

namespace ns2 {

class derived:
    private base_from_member<complex<int> >,
    private base_from_member<string, 1>,
    private base_from_member<string, 2>,
    public base, public base2
{
    typedef base_from_member<complex<int> > pbase_type;
    typedef base_from_member<string, 1>     pbase_type1;
    typedef base_from_member<string, 2>     pbase_type2;
    public:
    derived(int a, int b):
        pbase_type(a, b),
        pbase_type1("str1"),pbase_type2("str2"),
        base(pbase_type::member),
        base2(pbase_type1::member, pbase_type2::member)
    {
        cout << "derived ctor2" << endl;
        cout << pbase_type::member << endl;
    }
};

}

void case2()
{
    ns2::derived d(10, 20);
}

///////////////////////////////////////

namespace ns3 {

class pbase_type
{
protected:
    complex<int> cp;
    string x,y;
    pbase_type(int a, int b, string c, string d):
        cp(a,b), x(c), y(d)
{}
};

class derived: private pbase_type, public base, public base2
{
public:
    derived(int a, int b):
        pbase_type(a, b, "str1", "str2"),
        base(cp), base2(x, y)
{
    cout << "derived ctor3" << endl;
    cout << cp << endl; 
}

};

}

void case3()
{
    ns3::derived d(10, 20);
}

///////////////////////////////////////

int main()
{
    std::cout << "hello base_from_member" << std::endl;

    case1();
    case2();
    case3();
}
