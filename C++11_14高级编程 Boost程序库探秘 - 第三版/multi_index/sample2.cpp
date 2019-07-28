// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/foreach.hpp>
#include <boost/assign.hpp>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/key_extractors.hpp>
using namespace boost::multi_index;
namespace mi = boost::multi_index;

int main()
{
    typedef multi_index_container<int,
        indexed_by<
            ordered_unique<identity<int>>,
            hashed_unique <identity<int>>
            >
        > mic_t;
    mic_t mic = {2, 1, 7, 6, 8};

    //using namespace boost::assign;
    //insert(mic)(2), 1, 7, 6, 8;

    assert(mic.size() == 5);
    assert(mic.count(2) == 1);
    assert(mic.find(10) == mic.end());

    auto& hash_index = mic.get<1>();

    assert(hash_index.size() == 5);
    assert(hash_index.count(2) == 1);
    assert(hash_index.find(10) == hash_index.end());

    BOOST_FOREACH(int i, hash_index)
    {
        cout << i << ",";
    }
    cout << endl;

    for(int i : mic)
    {
        cout << i << ',';
    }
    cout << endl;

}

