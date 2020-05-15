// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/core/ignore_unused.hpp>

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/assign/ptr_list_inserter.hpp>

#include <boost/assign.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/functional/hash.hpp>
#include <boost/tuple/tuple.hpp>
using namespace boost;

#define BOOST_MULTI_INDEX_DISABLE_SERIALIZATION

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/key_extractors.hpp>

using namespace boost;
using namespace boost::multi_index;

namespace mi = boost::multi_index;

///////////////////////////////////////

#include "person.hpp"

///////////////////////////////////////

void case1()
{
    typedef composite_key<person*,
        BOOST_MULTI_INDEX_MEMBER(person, int, m_id),
        BOOST_MULTI_INDEX_MEMBER(person, string, m_fname)
    > comp_key;

    typedef multi_index_container<
        person*,
        indexed_by<
            ordered_unique<comp_key>
        >
    > mic_t;

    ptr_vector<person> vec;
    using namespace boost::assign;

    ptr_push_back(vec)
        (2, "agent", "smith")
        (1, "anderson", "neo")
        (1, "the one", "neo");

    mic_t mic;
    for(auto& p : vec)
    {
        mic.insert(&p);
    }

    for(auto p : mic)
    {
        cout << p->m_id << ":" << p->m_fname << ",";
    }

    cout << endl;

    assert(mic.count(boost::make_tuple(1, "anderson")) == 1);
    assert(mic.find(boost::make_tuple(2, "agent")) != mic.end());

    assert(mic.count(make_tuple(1)) == 2);
    assert(mic.count(1) == 2);
}

///////////////////////////////////////

void case2()
{
    typedef composite_key<person*,
        BOOST_MULTI_INDEX_MEMBER(person, int, m_id),
        BOOST_MULTI_INDEX_MEMBER(person, string, m_fname)
    > comp_key;

    typedef composite_key_compare<
        std::less<int>,
        std::greater<string>
    > comp_key_compare;

    typedef multi_index_container<
        person*,
        indexed_by<
            ordered_unique<
                comp_key,
                comp_key_compare
            >
        >
    > mic_t;

    typedef multi_index_container<
        person*,
        indexed_by<
            ordered_unique<
                comp_key,
                composite_key_result_greater<comp_key::result_type>
            >
        >
    > mic_t2;

    boost::ignore_unused<mic_t, mic_t2>();
}

///////////////////////////////////////

int main()
{
    std::cout << "hello composite_key" << std::endl;

    case1();
}
