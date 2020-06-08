// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
//using namespace std;

#include <boost/checked_delete.hpp>
#include <boost/core/ignore_unused.hpp>

#include <boost/functional/factory.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    auto pi = factory<int*>()();
    auto ps = factory<std::string*>()();
    auto pp = factory<std::pair<int, double>*>()();

    checked_delete(pi);
    checked_delete(ps);
    checked_delete(pp);

    auto up = factory<std::unique_ptr<int> >()();
    auto sp = factory<std::shared_ptr<std::string> >()();

}

///////////////////////////////////////

void case2()
{
    int a = 10, b = 20;
    auto pi = factory<int*>()(a);
    auto ps = factory<std::string*>()("char* lvalue");
    auto pp = factory<std::pair<int, int>*>()(a, b);

    checked_delete(pi);
    checked_delete(ps);
    checked_delete(pp);

    //auto pi2 = factory<int*>()(10);
    //auto pp2 = factory<std::pair<int, int>*>()(1, 2);

    auto p = std::bind(factory<int*>(),10)();
    checked_delete(p);
}

///////////////////////////////////////

#include <boost/functional/value_factory.hpp>
#include <boost/bind.hpp>

void case3()
{
    auto i  = value_factory<int>()();
    auto str    = value_factory<std::string>()("hello");
    auto p  = value_factory<std::pair<int, std::string>>()(i, str);

    {
        auto i  = bind(value_factory<int>(), 10)();

        boost::ignore_unused(i);
    }
}

///////////////////////////////////////

int main()
{
    std::cout << "hello factory" << std::endl;

    case1();
    case2();
    case3();
}
