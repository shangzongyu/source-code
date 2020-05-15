// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/ptr_container/ptr_map.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    typedef ptr_map<int, string> ptr_map_t;
    ptr_map_t m;

    int a = 1;
    m.insert(a, new string("one"));
    m.insert(10, auto_ptr<string>(new string("ten")));

    assert(m.size() == 2);
    assert(m[10] == "ten");

    m.replace(m.begin(), new string("neo"));
    m[3] = "three";
    assert(m.at(1) == "neo" && m.at(3) == "three");

    for(const auto& i : m)
    //for(const ptr_map_t::value_type& i : m)
    {
        cout << *i->second << ",";
    }

    typedef ptr_multimap<int, string> ptr_multimap_t;
    ptr_multimap_t mm;

    mm.transfer(m.begin(), m);
    assert(m.size() == 2);
    assert(mm.count(1) == 1);

}

///////////////////////////////////////

void case2()
{
    typedef ptr_map<int, nullable<string> > ptr_map_t;
    ptr_map_t m;

    m.insert(10, auto_ptr<string>(new string("ten")));
    m.at(10) = "tenten";

    //m[3] = "three";

}

///////////////////////////////////////

int main()
{
    std::cout << "hello ptr_map" << std::endl;

    case1();
    case2();
}




