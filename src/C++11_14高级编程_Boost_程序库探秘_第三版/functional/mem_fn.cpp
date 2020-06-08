// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
#include <stack>
//using namespace std;

#include <boost/mem_fn.hpp>
using namespace boost;

class demo_class
{
public:
    int x;
    demo_class(int a = 0):x(a){}

    void print()
    {
        std::cout << x << std::endl;
    }

    void hello(const char* str)
    {
        std::cout << str << std::endl;
    }
};

///////////////////////////////////////

void case1()
{
    demo_class d;
    mem_fn(&demo_class::print)(d);

    demo_class *p = &d;
    mem_fn(&demo_class::hello)(p, "hello");

    std::unique_ptr<demo_class> up(new demo_class(100));
    mem_fn(&demo_class::print)(up);
    assert(up.get() != 0);

    std::shared_ptr<demo_class> sp(new demo_class);
    mem_fn(&demo_class::hello)(sp, "world");

    std::vector<demo_class> v(10);
    std::for_each(v.begin(), v.end(),
            mem_fn(&demo_class::print));

    std::cout << "mem var : " << mem_fn(&demo_class::x)(d) << std::endl;
}

///////////////////////////////////////
#include <boost/bind.hpp>

void case2()
{
    demo_class d;

    bind(&demo_class::print, _1)(d);
    bind(&demo_class::hello, _1, "hello")(&d);

    std::vector<demo_class> v(10);
    std::for_each(v.begin(), v.end(),
            bind(&demo_class::hello, _1, "world"));         //调用有参成员函数

}

///////////////////////////////////////

int main()
{
    std::cout << "hello mem_fn" << std::endl;

    case1();
    case2();
}
