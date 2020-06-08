// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/core/ignore_unused.hpp>

///////////////////////////////////////

void case1()
{
    int x = 0;
    int* p = &++x;
    assert(p);
    ++x = 10;

    //p = &x++;
}

///////////////////////////////////////

void case2()
{
    int x = 0;

    int& r1 = ++x;
    int&& r2 = x++;
    const int& r3 = x++;
    const int&& r4 = x++;

    cout << r1 << "," << r2 << "," << r3 << endl;

    boost::ignore_unused(r1, r2, r3, r4);
}

///////////////////////////////////////

class moveable
{
private:
    int x;
public:
    moveable() {}
    moveable(moveable&& other)
    {
        std::swap(x, other.x);
    }

    moveable& operator=(moveable&& other)
    {
        std::swap(x, other.x);
        return *this;
    }
public:
    static moveable create()
    {
        moveable obj;
        return obj;
    }
};

void case3()
{
    moveable m1;

    moveable m2(std::move(m1));

    moveable m3 = moveable::create();


    boost::ignore_unused(m1, m2, m3);
}

///////////////////////////////////////

void case4()
{
    vector<complex<double>> v;

    v.emplace_back(3,4);
    assert(v.size() == 1);

    map<string, string> m;

    m.emplace("metroid", "prime");
    assert(m.size() == 1);
}

///////////////////////////////////////

void check(int&)
{
    cout << "lvalue" << endl;
}

void check(int&&)
{
    cout << "rvalue" << endl;
}

template<typename T>
void print(T&& v)
{
    check(std::forward<T>(v));
}

void case5()
{
    int x = 10;

    print(x);
    print(std::move(x));
}

///////////////////////////////////////

int main()
{
    std::cout << "hello C++11/14 rvalue" << std::endl;

    case1();
    case2();
    case3();
    case4();
    case5();
}
