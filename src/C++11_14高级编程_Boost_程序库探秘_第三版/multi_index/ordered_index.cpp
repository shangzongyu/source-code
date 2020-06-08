// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/assign.hpp>
#include <boost/foreach.hpp>
using namespace boost;

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/key_extractors.hpp>
using namespace boost::multi_index;

///////////////////////////////////////

void case1()
{
    using namespace boost::assign;

    typedef multi_index_container<int,
        indexed_by<
            ordered_unique<identity<int>>
        >
    > mic_t1;

    mic_t1 mic1;
    insert(mic1)(2), 3, 5, 7, 11;

    assert(mic1.size() == 5);
    assert(!mic1.insert(3).second);
    assert(mic1.find(7) != mic1.end());
}

///////////////////////////////////////

void case2()
{
    using namespace boost::assign;

    typedef multi_index_container<string,
        indexed_by<
            ordered_non_unique<
                BOOST_MULTI_INDEX_CONST_MEM_FUN(string, size_t, size)>
        >
    > mic_t2;

    mic_t2 mic2;
    insert(mic2)("111")("22")("333")("4444");
    assert(mic2.count(3) == 2);

    BOOST_FOREACH(auto& str, mic2.equal_range(3))
    {   cout << str << ",";}

    cout << endl;
}

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

struct lower_bounder
{
    typedef bool result_type;
    bool operator()(const person& p)
    {   return p.m_id >= 2;}
};
struct upper_bounder
{
    typedef bool result_type;
    bool operator()(const person& p)
    {   return p.m_id < 20;}
};

void case3()
{
    using namespace boost::assign;

    typedef multi_index_container<person,
        indexed_by<
            ordered_unique<identity<person>>
        >
    > mic_t;

    mic_t mic;
    insert(mic)
        (person(2, "agent", "smith"))
        (person(20, "lee", "someone"))
        (person(1, "anderson", "neo"))
        (person(10, "lee", "bruce"));

    assert(mic.count(person(1, "abc","xby")) == 1);

    assert(mic.count(1, compare_by_id()) == 1);
    assert(mic.find(10, compare_by_id()) != mic.end());

    mic_t::iterator l = mic.lower_bound(2 , compare_by_id());

    mic_t::iterator u = mic.lower_bound(20, compare_by_id());

    //BOOST_FOREACH(const person& p, std::make_pair(l, u))

    //BOOST_FOREACH(const person& p,
    //    mic.range(lower_bounder(), upper_bounder()))

    BOOST_FOREACH(const person& p,
        mic.range(
            [](const person& p){ return p.m_id >= 2;},
            [](const person& p){ return p.m_id <  20;}
        ))
    {
        cout << p.m_id << ":"
            << nameof(p) << endl;
    }

}

///////////////////////////////////////

int main()
{
    std::cout << "hello ordered_index" << std::endl;

    case1();
    case2();
    case3();
}
