// Copyright (c) 2016
// Author: Chrono Law
#include <memory>
#include <std.hpp>
using namespace std;

#include <boost/core/ignore_unused.hpp>

///////////////////////////////////////

class default_demo
{
public:
    default_demo() = default;
    ~default_demo() = default;

    default_demo(const default_demo&) = default;
    default_demo& operator=(const default_demo&) = default;

    default_demo(default_demo&&) = default;
    default_demo& operator=(default_demo&&) = default;
public:
    default_demo(int x) {}
};

void case1()
{
    default_demo d;

    boost::ignore_unused(d);
}

///////////////////////////////////////

class delete_demo
{
public:
    delete_demo() = default;
    ~delete_demo() = default;

    delete_demo(const delete_demo&) = delete;
    delete_demo& operator=(const delete_demo&) = delete;
};

void case2()
{
    delete_demo d1;
    //delete_demo d2 = d1;

    boost::ignore_unused(d1);
}

///////////////////////////////////////

struct base
{
    virtual ~base() = default;

    virtual void f() = 0;
    virtual void g() const
    {   cout << "base g()" << endl;}
    void h()
    {   cout << "base h()" << endl;}
};

//struct derived : public base
//{
//    virtual ~derived() = default;
//
//    void f()
//    {   cout << "derived f()" << endl;}
//    void g()
//    {   cout << "derived g()" << endl;}
//    void h()
//    {   cout << "derived h()" << endl;}
//};

struct derived : public base
{
    virtual ~derived() = default;

    void f() override
    {   cout << "derived f()" << endl;}
    void g() const override
    {   cout << "derived g()" << endl;}
    void h() //override
    {   cout << "derived h()" << endl;}
};

void case3()
{
    unique_ptr<base> p(new derived);

    p->f();
    p->g();
    p->h();

}

///////////////////////////////////////

struct interface
{
    virtual ~interface() = default;

    virtual void f() = 0;
    virtual void g() = 0;
};

struct abstract : public interface
{
    virtual ~abstract() = default;

    void f() override final {}
    void g() override {}
};

struct last final : public abstract
{
    virtual ~last() = default;

    //void f() override {}
    void g() override {}
};

//struct error : public last
//{};

///////////////////////////////////////

void case4()
{
    class demo
    {
    public:
        int x = 0;
        string s = "hello";
        vector<int> v{1,2,3};
    };

    demo d;

    assert(d.x == 0);
    assert(d.s == "hello");
    assert(d.v.size() == 3);
}

///////////////////////////////////////

class demo
{
private:
    int x,y;
    //void init(int a, int b)
    //{
    //    x=a;y=b;
    //}
public:
    demo() : demo(0, 0) {}
    //{
    //    init(0, 0);
    //}

    demo(int a) : demo(a, 0) {}
    //{
    //    init(a, 0);
    //}

    demo(int a, int b)
    {
        x=a;y=b;
        //init(a, b);
    }
};

void case5()
{
}

///////////////////////////////////////

int main()
{
    std::cout << "hello C++11/14 class" << std::endl;

    case1();
    case2();
    case3();
    case4();
    case5();
}

