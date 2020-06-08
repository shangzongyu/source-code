// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/core/ignore_unused.hpp>

///////////////////////////////////////

void case1()
{
    int a[] = {2,3,5,7};

    for(int i = 0;i < 4; ++i)
    {
        cout << a[i] << ",";
    }
    cout << endl;

    vector<int> v = {253, 874};
    for(auto iter = v.begin(); iter != v.end(); ++iter)
    {
        cout << *iter << ",";
    }
    cout << endl;
}

///////////////////////////////////////

void case2()
{
    int a[] = {2,3,5,7};

    for(auto&& x : a)
    {
        cout << x << ",";
    }
    cout << endl;

    vector<int> v = {253, 874};
    for(const auto& x : v)
    {
        cout << x << ",";
    }
    cout << endl;

    for(auto& x : v)
    {
        cout << ++x << ",";
    }
    cout << endl;

    auto&& _range = v;
    for(auto _begin = std::begin(_range),
             _end = std::end(_range);
         _begin!= _end; ++_begin)
    {
        auto x = *_begin;
        boost::ignore_unused(x);
    }
}

///////////////////////////////////////

namespace std {

template<typename I>
auto begin(const std::pair<I, I>& p) ->decltype(p.first)
{
    return p.first;
}

template<typename I>
auto end(const std::pair<I, I>& p) -> decltype(p.second)
{
    return p.second;
}

}   //namespace std

void case3()
{
    vector<int> v = {1,2,3,4,5};

    auto r = std::make_pair(v.begin(), v.begin() + 3);

    for(auto x : r)
    {
        cout << x << ",";
    }
}

///////////////////////////////////////

int main()
{
    std::cout << "hello C++11/14 for" << std::endl;

    case1();
    case2();
    case3();
}
