// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/multi_index/key_extractors.hpp>

using namespace boost::multi_index;
namespace mi = boost::multi_index;

#include "person.hpp"

///////////////////////////////////////

void case1()
{
    assert((is_same<string, identity<string>::result_type>::value));
    assert(identity<int>()(10) == 10);
    assert(identity<string>()("abc") == "abc");

    int* p      = new int(100);
    int** pp    = &p;
    assert(identity<int>()(pp) == 100);

}

///////////////////////////////////////

void case2()
{
    typedef pair<int, string> pair_t;
    pair_t p(1, "one");

    assert((member<pair_t, int, &pair_t::first>()(p)        == 1));
    assert((member<pair_t, string, &pair_t::second>()(p)    == "one"));

    person per(1, "anderson", "neo");
    assert((member<person, int, &person::m_id>()(per)       == 1));

    assert((BOOST_MULTI_INDEX_MEMBER(pair_t, int, first)()(p)       == 1));
    assert((BOOST_MULTI_INDEX_MEMBER(pair_t, string, second)()(p)   == "one"));
    assert((BOOST_MULTI_INDEX_MEMBER(person, int, m_id)()(per)      == 1));

}

///////////////////////////////////////

void case3()
{
    typedef BOOST_MULTI_INDEX_CONST_MEM_FUN(person, \
            const string&, first_name) cmf_t2;
    typedef BOOST_MULTI_INDEX_CONST_MEM_FUN(string, size_t, size) cmf_t;

    string str("abc");
    //typedef const_mem_fun<string, size_t, &string::size > cmf_t;
    assert(cmf_t()(str) == 3);

    person per(1, "anderson", "neo");
    //typedef const_mem_fun<person, const string&, &person::first_name> cmf_t2;
    assert((cmf_t2()(per) == "anderson"));

}

///////////////////////////////////////

void case4()
{
    person per(1, "anderson", "neo");
    typedef global_fun<const person&, string, &nameof> gf_t;
    assert(gf_t()(per) == "anderson neo");

}

///////////////////////////////////////

int main()
{
    std::cout << "hello key_extractor" << std::endl;

    case1();
    case2();
    case3();
    case4();
}
