// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/ptr_container/ptr_vector.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    typedef ptr_vector<string> ptr_vec;
    ptr_vec vec;

    vec.push_back(new string("123"));
    vec.push_back(new string("abc"));

    assert(vec.front() == "123");
    assert(vec.back() == "abc");

    ptr_vec vec2;
    vec2.assign(vec.begin(), vec.end());
    assert(vec2.size() == 2);

    assert(*vec2.pop_back() == "abc");
    assert(vec2.size() == 1);

    vec.resize(5);
    assert(vec.back().empty());

    vec.resize(10, new string("xyz"));
    assert(vec.back() == "xyz");

    vec.transfer(vec.end(), vec2.begin(), vec2);
    assert(vec.size() == 11);
    assert(vec2.size() == 0);

    vec2.transfer(vec2.end(), vec.begin(),vec.begin() + 5, vec);
    assert(vec.size() == 6);
    assert(vec2.size() == 5);

    vec.transfer(vec.begin(), vec2);
    assert(vec.size() == 11);
    assert(vec2.size() == 0);

}

///////////////////////////////////////

int main()
{
    std::cout << "hello ptr_sequence_adapter" << std::endl;

    case1();
}
