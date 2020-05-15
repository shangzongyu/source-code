// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/utility/addressof.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    int i;
    string s;

    assert(&i == boost::addressof(i));
    assert(&s == boost::addressof(s));

    int a[10];

    assert(&a    == boost::addressof(a));
    assert(a + 1 == boost::addressof(a[1]));
    assert(&printf == boost::addressof(printf));
}

///////////////////////////////////////

class dont_do_this
{
public:
    int x,y;
    size_t operator&() const
    {   return (size_t)&y;  }
};

void case2()
{
    dont_do_this d;
    assert(&d != (size_t)boost::addressof(d));
    assert(&d == (size_t)&d.y);
    dont_do_this *p = boost::addressof(d);
    p->x = 1;

}

///////////////////////////////////////
class danger_class
{
    void operator&() const;
};

void case3()
{
    danger_class d;
    // cout << &d;
    cout << boost::addressof(d);
}


///////////////////////////////////////

int main()
{
    std::cout << "hello addressof" << std::endl;

    case1();
    case2();
    case3();
}
