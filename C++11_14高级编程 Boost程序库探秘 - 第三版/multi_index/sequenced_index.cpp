// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/sequenced_index.hpp>
using namespace boost::multi_index;

int main()
{
    std::cout << "hello sequenced_index" << std::endl;

    typedef multi_index_container<int,
            indexed_by<sequenced<
                tag<int, struct int_seq> > >
                > mic_t;

    //using namespace boost::assign;
    //mic_t mic = (list_of(2),3,5,7,11);
    mic_t mic = {2,3,5,7,11};

    assert(!mic.empty() && mic.size() == 5);

    assert(mic.front() == 2);
    assert(mic.back() == 11);

    assert(mic.push_front(2).second);
    assert(mic.push_back(19).second);

    auto& seq_index = mic.get<int_seq>();

    seq_index.insert(seq_index.begin(), 5, 100);
    assert(std::count(seq_index.begin(), mic.end(), 100) == 5);

    seq_index.unique();
    assert(std::count(seq_index.begin(), mic.end(), 100) == 1);

    //mic_t mic1 = (list_of(2),3,5,7,11);
    mic_t mic1 = {2,3,5,7,11};

    mic_t mic2 = mic1;
    assert(mic1 == mic2);

    mic2.push_back(3);
    assert(mic1 < mic2);

    //*seq_index.begin() = 9;

    auto& x = mic.front();
    assert(mic.begin() == mic.iterator_to(x));
    assert(mic.begin() != mic.iterator_to(2));

}

