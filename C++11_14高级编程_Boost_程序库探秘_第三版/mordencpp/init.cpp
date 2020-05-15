// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/core/ignore_unused.hpp>

///////////////////////////////////////

set<int> get_set()
{
    return {2,4,6};
}

void case1()
{
    int x{};
    double y{2.718};
    complex<double> c{1,1};
    string s{"venom snake"};

    assert(x == 0);
    boost::ignore_unused(y, s);

    int a[] = {1,2,3};
    vector<int> v = {4,5,6};

    auto ss = get_set();
    assert(ss.size() == 3);

    boost::ignore_unused(a, v);
}

///////////////////////////////////////

int main()
{
    std::cout << "hello C++11/14 init" << std::endl;

    case1();
}
