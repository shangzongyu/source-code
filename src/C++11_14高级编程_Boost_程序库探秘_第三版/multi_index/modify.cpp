// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/assign.hpp>
#include <boost/functional/hash.hpp>
#include <boost/foreach.hpp>
using namespace boost;

#include <boost/multi_index_container.hpp>
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

void case1()
{
    using namespace boost::assign;

    typedef multi_index_container<person,
        indexed_by<
            ordered_unique<identity<person>>,
            ordered_non_unique<
                member<person, string, &person::m_fname>>,
            hashed_unique<identity<person>>
        >
    > mic_t;

    mic_t mic;
    insert(mic)
        (person(2, "agent", "smith"))
        (person(20, "lee", "someone"))
        (person(1, "anderson", "neo"))
        (person(10, "lee", "bruce"));

    auto pos = mic.find(20, compare_by_id());
    assert(pos != mic.end());

    mic.replace(pos, person(20, "lee", "long"));
    assert(pos->m_lname == "long");

    assert(!mic.replace(pos, person(2, "lee", "someone")));
    assert(!mic.replace(pos, person(10, "lee", "bruce")));

}

///////////////////////////////////////

void modify_id(person& p, int id)
{
    p.m_id = id;
}
void modify_fname(person& p, const string& fname)
{
    p.m_fname = fname;
}
struct modify_lname
{
    string m_lname;
    modify_lname(const string& lname):
        m_lname(lname){}
    void operator()(person& p)
    {
        p.m_lname = m_lname;
    }
};

void case2()
{
    using namespace boost::assign;

    typedef multi_index_container<person,
        indexed_by<
            ordered_unique<identity<person>>,
            ordered_non_unique<
                member<person, string, &person::m_fname>>,
            hashed_unique<identity<person>>
        >
    > mic_t;

    mic_t mic;
    insert(mic)
        (person(2, "agent", "smith"))
        (person(20, "lee", "someone"))
        (person(1, "anderson", "neo"))
        (person(10, "lee", "bruce"));

    auto pos = mic.find(20, compare_by_id());
    assert(pos != mic.end());

    //mic.modify(pos, bind(&modify_id, _1, 15));
    mic.modify(pos, [](person& p){
                    p.m_id = 15; });
    assert(pos->m_id == 15);

    //mic.modify(pos, bind(&modify_fname, _1, "mike"));
    mic.modify(pos, [](person& p){
            p.m_fname = "mike";});
    assert(pos->m_fname == "mike");

    //mic.modify(pos, modify_lname("david"));
    mic.modify(pos, [](person& p){
            p.m_lname = "david";});
    assert(pos->m_lname == "david");

}

///////////////////////////////////////

void case3()
{
    using namespace boost::assign;

    typedef multi_index_container<person,
        indexed_by<
            ordered_unique<identity<person>>,
            ordered_non_unique<
                member<person, string, &person::m_fname>>,
            hashed_unique<identity<person>>
        >
    > mic_t;

    mic_t mic;
    insert(mic)
        (person(2, "agent", "smith"))
        (person(20, "lee", "someone"))
        (person(1, "anderson", "neo"))
        (person(10, "lee", "bruce"));

    auto pos = mic.find(20, compare_by_id());
    assert(pos != mic.end());

    auto tmp = pos->m_id;
    assert(!mic.modify(pos,
        [](person& p){p.m_id = 1;},
        [&](person& p){p.m_id = tmp;}));

    //assert(!mic.modify(pos, bind(&modify_id, _1, 1)));
    assert(!mic.modify(pos,
        [](person& p){p.m_id = 1;}));

    assert(mic.size() == 3);
    assert(mic.find(20, compare_by_id()) == mic.end());

}

///////////////////////////////////////

void case4()
{
    using namespace boost::assign;

    typedef multi_index_container<person,
        indexed_by<
            ordered_unique<identity<person>>,
            ordered_non_unique<
                member<person, string, &person::m_fname>>,
            hashed_unique<identity<person>>
        >
    > mic_t;

    mic_t mic;
    insert(mic)
        (person(2, "agent", "smith"))
        (person(20, "lee", "someone"))
        (person(1, "anderson", "neo"))
        (person(10, "lee", "bruce"));

    auto& index = mic.get<1>();
    auto pos = index.find("agent");

    //index.modify_key(pos, bind(&modify_str, _1, "virus"));
    index.modify_key(pos,
        [](string& str){  str = "virus";});
    assert(pos->m_fname == "virus");

    auto tmp = pos->m_fname;
    index.modify_key(pos,
            [](string& str){  str = "virus";},
            [&](string& str){  str = tmp;});

}

///////////////////////////////////////

int main()
{
    std::cout << "hello modify" << std::endl;

    case1();
    case2();
    case3();
    case4();
}
