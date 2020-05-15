// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/range.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    vector<int> v(10);

    //typedef iterator_range<vector<int>::iterator> vec_range;
    //vec_range r1(v);

    auto r1 = make_iterator_range(v);

    assert(!r1.empty());
    assert(r1.size() == 10);

    int a[10];

    //typedef iterator_range<int*> int_range;
    //int_range r2(a, a + 5);

    auto r2 = make_iterator_range(a, a + 5);

    assert(r2.size() == 5);

    auto r3 = make_iterator_range(a, 1, -1);
    assert(r3.size() == 8);

}

///////////////////////////////////////

#include <boost/algorithm/string.hpp>

void case2()
{
    char a[] = "iterator range";

    auto r = boost::find_first(a, " ");
    assert(r.front() == ' ');

    auto r2 = make_iterator_range(a, r.begin());
    assert(copy_range<string>(r2) == "iterator");

}

///////////////////////////////////////

#include <boost/range/counting_range.hpp>
#include <boost/range/istream_range.hpp>
#include <boost/range/irange.hpp>

void case3()
{
    boost::copy(
        counting_range(0,10),  ostream_iterator<int>(cout, ","));

    cout << endl;

    //boost::copy(istream_range<int>(cin), ostream_iterator<int>(cout, ","));

    boost::copy(irange(0,10), ostream_iterator<int>(cout, ","));

    cout << endl;

    boost::copy(irange(0,20,2), ostream_iterator<int>(cout, ","));

    cout << endl;
}

///////////////////////////////////////

#include <boost/range/combine.hpp>

void case4()
{
    string str = "abcde";
    vector<int> v = {5,4,3,2,1};

    auto r = combine(str, v);

    for(const auto& x : r)
    {
        auto& c = get<0>(x);
        auto& i = get<1>(x);
        cout << "(" << c << "," << i << ") ";
    }

    cout << endl;

    //string s2 = "xyz";

    //auto r2 = combine(s2, v);

    //for(const auto& x : r2)
    //{
    //    auto& c = get<0>(x);
    //    auto& i = get<1>(x);
    //    cout << "(" << c << "," << i << ") ";
    //}

}

///////////////////////////////////////

#include <boost/range/any_range.hpp>

void case5()
{
    list<int> l = {1,3,5,7,9};

    //typedef any_range_type_generator<decltype(l)>::type range_type;
    typedef any_range<int, boost::single_pass_traversal_tag> range_type;

    range_type r(l);

    for(const auto& x : r)
    {
        cout << x << ",";
    }

    cout << endl;

    vector<int> v = {2,4,6,8,0};

    r = v;

    for(const auto& x : r)
    {
        cout << x << ",";
    }

    cout << endl;

    set<int> s = {-1,-2,-3};

    r = s;

    for(const auto& x : r)
    {
        cout << x << ",";
    }
}

///////////////////////////////////////

int main()
{
    std::cout << "hello iterator_range" << std::endl;

    case1();
    case2();
    case3();
    case4();
    case5();
}

