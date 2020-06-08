// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/assign.hpp>
#include <boost/foreach.hpp>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/key_extractors.hpp>

using namespace boost::multi_index;
namespace mi = boost::multi_index;

#include "person.hpp"

///////////////////////////////////////

int main()
{
    typedef multi_index_container<
        person,
        indexed_by<
            sequenced<>,
        ordered_unique<identity<person>>,
        ordered_non_unique<
            member<person, string, &person::m_fname>>,
        hashed_unique<identity<person>>
            >
            > mic_t;

    mic_t mic;
        //= {
        //person(2, "agent", "smith"),
        //person(20, "lee", "someone"),
        //person(1, "anderson", "neo"),
        //person(10, "lee", "bruce")
        //};

    using namespace boost::assign;
    push_front(mic)
        (person(2, "agent", "smith"))
        (person(20, "lee", "someone"))
        (person(1, "anderson", "neo"))
        (person(10, "lee", "bruce"));

    auto& index0 = mic.get<0>();
    auto& index1 = mic.get<1>();
    auto& index2 = mic.get<2>();
    auto& index3 = mic.get<3>();

    for(const person& p : index0)
    {
        cout << p.m_id << p.m_fname << ",";
    }

    assert(index1.begin()->m_id == 1);

    assert(index2.count("lee") == 2);

    insert(index2)(person(30, "lee", "test"));
    assert(index3.size() == 5);

    assert(!index2.insert(person(2, "lee", "test2")).second);
}

