// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/range.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    vector<int> v{7,8,4,6,53,2,6};

    boost::copy(
            boost::sort(v) |
            adaptors::uniqued,
            ostream_iterator<int>(cout, ","));

    cout << endl;

    assert(boost::count(v, 6) == 2);

    auto even = [](int x){ return x%2==0;};

    assert( boost::distance(
                v | adaptors::filtered(even)) == 5);

    boost::copy(v | adaptors::copied(0,5),
            ostream_iterator<int>(cout, ","));
    cout << endl;

    cout << "---" << endl;

    boost::copy(v | adaptors::filtered(even),
        ostream_iterator<int>(cout, ","));
    cout << endl;

    boost::copy(v | adaptors::reversed,
        ostream_iterator<int>(cout, ","));
    cout << endl;

    boost::copy(v |
        adaptors::filtered(even) | adaptors::reversed,  
            ostream_iterator<int>(cout, ","));
    cout << endl;
}

///////////////////////////////////////

int main()
{
    std::cout << "hello iterator adaptors" << std::endl;

    case1();
}
