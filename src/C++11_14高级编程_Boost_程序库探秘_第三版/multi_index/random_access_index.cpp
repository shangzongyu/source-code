// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/assign.hpp>
using namespace boost;

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/random_access_index.hpp>
using namespace boost::multi_index;

int main()
{
    typedef multi_index_container<int,
        indexed_by<random_access<> >
        > mic_t;

    using namespace boost::assign;
    mic_t mic1 = (list_of(2),3,5,7,11);

    assert(mic1[0] == 2);
    assert(mic1.at(2) == 5);

    mic1.erase(boost::next(mic1.begin(), 2));
    assert(mic1[2] == 7);

    mic_t mic2;
    mic2.splice(mic2.end(), mic1);
    assert(mic1.empty() && mic2.size() == 4);

    push_front(mic1)(8), 10, 20, 16;

    mic1.sort();
    mic2.sort();

    mic1.merge(mic2);

    for (auto iter = mic1.rbegin();
        iter != mic1.rend(); ++iter)
    {
        cout << *iter << ",";
    }

    //std::sort(mic1.begin(), mic1.end());
    //std::random_shuffle(mic1.begin(), mic1.end());
    //std::replace(mic1.begin(), mic1.end(), 2, 222);

}

