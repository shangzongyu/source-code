// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/core/ignore_unused.hpp>

///////////////////////////////////////

void case1()
{
    //auto f1 = [](){};

    auto f1 = [](int x){
        return x*x;
        };

    auto f2 = [](string s) {
        cout << "lambda : " << s << endl;
        };

    auto f3 = [](int x, int y) {
        return x < y;
        };

    cout << f1(3) << endl;
    f2("heavy rain");
    cout << f3(1,5) << endl;

    vector<int> v = {1,3,5,7};
    std::for_each(v.begin(), v.end(), [](int x ){
        cout << x << ",";
        });
    cout << endl;

    std::for_each(v.begin(), v.end(), [](int& x ){
        if(x > 3) { x *=2;}
        });

    for(auto&& x : v)
    {
        cout << x << ",";
    }
    cout << endl;

    auto f4 = [](int x) -> long {
        return x*x;
        };

    boost::ignore_unused(f1, f2, f3, f4);
}

///////////////////////////////////////

void case2()
{
    int x = 0, y = 0;

    //auto f1 = [](){return x;};  // error
    auto f1 = [=](){return x;};
    auto f2 = [&](){return ++x;};
    auto f3 = [x](){return x;};
    auto f4 = [x,&y](){y += x;};
    auto f5 = [&,y](){x += y;};
    auto f6 = [&](){y += ++x;};

    assert(f1() == 0 && x == 0);
    assert(f2() == 1 && x == 1);
    assert(f3() == 0);
    f4();assert(x == 1 && y == 0);
    f5();assert(x == 1 && y == 0);
    f6();assert(x == 2 && y == 2);
}

///////////////////////////////////////

void case3()
{
    int x = 0;

    auto f = [=]() mutable {return ++x;};
    assert(f() == 1 && x == 0);
}

///////////////////////////////////////

void case4()
{
    vector<int> v = {1,2,3,4,5};
    int sum = 0;

    std::for_each(v.begin(), v.end(),
        [&](int x){
            sum += x;
        });

    assert(sum == 15);

    int k = 3;
    auto c = std::count_if(
        v.begin(), v.end(),
        [=](int x){
            return x > k;
        });

    assert(c == 2);
}

///////////////////////////////////////

void case5()
{
    int x = 0;

    auto f = [](){};
    auto g = [&](){++x;};

    typedef void (*func)();

    func p1 = f;
    func p2 = [](){cout<<endl;};
    //func p3 = g;

    boost::ignore_unused(x, f, g, p1, p2);
}

///////////////////////////////////////

int main()
{
    std::cout << "hello C++11/14 lambda" << std::endl;

    case1();
    case2();
    case3();
    case4();
    case5();
}
