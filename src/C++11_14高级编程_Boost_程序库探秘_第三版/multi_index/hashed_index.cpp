// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/assign.hpp>
#include <boost/functional/hash.hpp>
#include <boost/foreach.hpp>
#include <boost/tuple/tuple.hpp>
using namespace boost;

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/key_extractors.hpp>

using namespace boost;
using namespace boost::multi_index;

namespace mi = boost::multi_index;

#include "person.hpp"

///////////////////////////////////////

typedef boost::tuple<int, string, string> hash_key_t;

struct hash_func
{
    typedef size_t result_type;
    size_t operator()(const hash_key_t& k) const        //必须是const
    {
        size_t seed = 2016;
        hash_combine(seed, k.get<1>());
        hash_combine(seed, k.get<2>());
        return seed;
    }
};

//定义相等比较函数对象
struct equal_func
{
    typedef bool result_type;
    bool operator()(const hash_key_t& k, const person& p) const
    {   return k.get<0>() == p.m_id;}
    bool operator()(const person& p, const hash_key_t& k) const
    {   return k.get<0>() == p.m_id;}
};

///////////////////////////////////////

int main()
{
    std::cout << "hello hashed_index" << std::endl;

    using namespace boost::assign;

    typedef multi_index_container<person,
            indexed_by<
                hashed_unique<mi::identity<person>>
                >
                > mic_t;

    mic_t mic;
    insert(mic)
        (person(2, "agent", "smith"))
        (person(1, "anderson", "neo"))
        (person(10, "lee", "bruce"));

    assert(mic.size() == 3);
    assert(mic.find(person(1, "anderson", "neo"))!= mic.end());

    assert(mic.count(boost::make_tuple(1, "anderson", "neo"),
            hash_func(), equal_func()) == 1);
    assert(mic.find(boost::make_tuple(10, "lee", "bruce"),
            hash_func(), equal_func())!= mic.end());

};

