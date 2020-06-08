// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/assign.hpp>
#include <boost/foreach.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
using namespace boost::multi_index;
namespace mi = boost::multi_index;

int main()
{
    multi_index_container<int> mic;
    assert(mic.empty());

    mic.insert(1);
    assert(mic.size() == 1);

    using namespace boost::assign;
    insert(mic)(2), 7, 6, 8;

    assert(mic.size()   == 5);
    assert(mic.count(2) == 1);
    assert(mic.find(10) == mic.end());

    for(int i : mic)
    {
        cout << i << ',';
    }
    cout << endl;

    decltype(mic) c = {1,2,3};
    for(int i : c)
    {
        cout << i << ',';
    }
    cout << endl;
}

