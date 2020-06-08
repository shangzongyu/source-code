// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/ptr_container/ptr_set.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    typedef ptr_set<string> ptr_set_t;
    ptr_set_t s;
    assert(s.empty());

    assert(s.insert(new string("fire")).second);
    assert(s.insert(new string("emblem")).second);
    assert(s.size() == 2);

    assert(!s.insert(new string("fire")).second);
    assert(s.size() == 2);

    auto ap = s.release();
    assert(s.empty());

    typedef ptr_multiset<string> ptr_mset_t;
    ptr_mset_t ms(ap->begin(), ap->end());
    assert(ms.size() == 2);

    ms.insert(new string("fire"));
    ms.insert(new string("emblem"));
    assert(ms.size() == 4);
    assert(ms.count("fire") == 2);

}

///////////////////////////////////////

int main()
{
    std::cout << "hello ptr_set" << std::endl;

    case1();
}



