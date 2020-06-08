// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/ptr_container/ptr_unordered_set.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    typedef ptr_unordered_set<string> ptr_set_t;
    ptr_set_t s;
    assert(s.empty());

    assert(s.insert(new string("king")).second);
    assert(s.insert(new string("kong")).second);
    assert(s.size() == 2);

    assert(!s.insert(new string("king")).second);
    assert(s.size() == 2);

    ptr_set_t s2;
    s2.transfer(s);
    assert(s.empty() && s2.size() == 2);

    typedef ptr_unordered_multiset<string> ptr_mset_t; 
    ptr_mset_t ms;

    ms.transfer(s2);
    assert(ms.size() == 2);

    ms.insert(new string("king"));
    ms.insert(new string("kong"));
    assert(ms.size() == 4);
    assert(ms.count("king") == 2);

}

///////////////////////////////////////

int main()
{
    std::cout << "hello ptr_unordered_set" << std::endl;

    case1();
}



