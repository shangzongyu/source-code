// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/assign.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/functional/hash.hpp>
#include <boost/foreach.hpp>
using namespace boost;

#define BOOST_MULTI_INDEX_DISABLE_SERIALIZATION

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/key_extractors.hpp>

using namespace boost;
using namespace boost::multi_index;

namespace mi = boost::multi_index;

///////////////////////////////////////

#include "person.hpp"

struct compare_by_id
{
    typedef bool result_type;
    bool operator()(const person& p, int id) const
    {   return p.m_id < id;}
    bool operator()(int id, const person& p) const
    {   return id < p.m_id ;}
};

///////////////////////////////////////

int main()
{
    std::cout << "hello multi_index_container" << std::endl;

    typedef sequenced<tag<int, struct seq_idx> >        idx_sf0;
    typedef random_access<tag<struct rnd_idx, string> > idx_sf1;

    typedef ordered_unique<mi::identity<person>> idx_sf2;
    typedef ordered_non_unique<
        BOOST_MULTI_INDEX_MEMBER(person, string, m_fname) > idx_sf3;
    typedef ordered_unique<
        BOOST_MULTI_INDEX_CONST_MEM_FUN(
            person, const string&, first_name),
        std::greater<const string> >                        idx_sf4;

    typedef hashed_unique<
        BOOST_MULTI_INDEX_MEMBER(person, string, m_lname) > idx_sf5;
    typedef hashed_non_unique<
        global_fun<const person&, string, &nameof> >    idx_sf6;
    typedef hashed_unique< person_name>                 idx_sf7;

    typedef multi_index_container<person,
        indexed_by<
            idx_sf0, idx_sf1,
            idx_sf2, idx_sf3, idx_sf4,
            idx_sf5, idx_sf6, idx_sf7
        >
    > mic_t;

    mic_t mic ;

    using namespace boost::assign;
    push_back(mic)
        (person(2, "agent", "smith"))
        (person(20, "lee", "someone"))
        (person(1, "anderson", "neo"))
        (person(10, "lee", "bruce"));

    assert(mic.size() == 3);

    auto& idx1 = mic.get<rnd_idx>();
    auto& idx2 = mic.get<2>();

    auto pos = idx2.find(1, compare_by_id());
    auto pos2 = mic.project<string>(pos);

    assert(pos2 == idx1.iterator_to(idx1[2]));

    typedef boost::shared_ptr<person> person_ptr;

    typedef hashed_unique<
        BOOST_MULTI_INDEX_MEM_FUN(
        person, string&, last_name)
    > idx_sf8;

    typedef multi_index_container<person_ptr,       //定义多索引容器
        indexed_by<idx_sf8> > mic_t2;

    mic_t2 mic2 ;
    mic2.insert(boost::make_shared<person>(2, "agent", "smith"));

}

