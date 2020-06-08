// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/range.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>
using namespace boost;

///////////////////////////////////////

#include <boost/range/irange.hpp>
#include <boost/range/join.hpp>

void case1()
{
    vector<int> v;
    boost::copy(boost::irange(0,10), std::back_inserter(v));

    auto r1 = make_iterator_range(v.begin(), v.begin() + 3);
    auto r2 = make_iterator_range(v.begin() + 5, v.end() );

    auto r3 = boost::join(r1, r2);

    boost::copy(r3, ostream_iterator<int>(cout, ","));

}

///////////////////////////////////////

int main()
{
    std::cout << "hello range join" << std::endl;

    case1();
}


