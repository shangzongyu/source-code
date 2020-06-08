// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/ptr_container/ptr_unordered_map.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    typedef ptr_unordered_map<int, string> ptr_map_t;
    ptr_map_t m;

    int a = 1;
    m.insert(m.begin(),a, new string("one"));
    m.insert(m.end(), 10,
                auto_ptr<string>(new string("ten")));
    m[3] = "three";

    assert(m.at(3) == "three");
    assert(m[10] == "ten");

    for(const auto& i : m)
    {
        cout << i->second << ",";
    }

    typedef ptr_unordered_multimap<int, string> ptr_multimap_t;
    ptr_multimap_t mm;

    mm.transfer(m.begin(), m.end(), m);
    assert(mm.size() == 3);
    assert(m.empty() );

}

///////////////////////////////////////

int main()
{
    std::cout << "hello ptr_unordered_map" << std::endl;

    case1();
}




