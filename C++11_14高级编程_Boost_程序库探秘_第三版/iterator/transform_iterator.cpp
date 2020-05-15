// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/iterator/counting_iterator.hpp>

#include <boost/iterator/transform_iterator.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    typedef counting_iterator<int> ci_t; 

    vector<int> v;
    std::copy(ci_t(0), ci_t(10), back_inserter(v));

    using std::placeholders::_1;

    auto f = bind(plus<int>(), _1, 5);

    std::copy(
        make_transform_iterator(v.begin(), f),
        make_transform_iterator(v.end(), f),
        ostream_iterator<int>(cout, " "));
}

///////////////////////////////////////

int main()
{
    std::cout << "hello transform_iterator" << std::endl;

    case1();
}

