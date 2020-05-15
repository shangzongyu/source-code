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

    assert((std::is_same<ptr_vec::value_type, string*>::value));
    assert((std::is_same<ptr_vec::pointer    , string*>::value));
    assert((std::is_same<ptr_vec::reference , string&>::value));

    ptr_vec vec;
    assert(vec.empty());

    vec.push_back(new string("123"));
    vec.push_back(new string("abc"));
    assert(vec.size() == 2);

    ptr_vec vec2(vec);
    assert(vec2.size() == 2);
    assert(vec.size() == 2);

    auto apv = vec.release();
    assert(vec.empty());

    ptr_vec vec3(apv);
    assert(vec3.size() == 2);

    ptr_vec vec4, vec5;

    vec4 = vec2;
    assert(vec2.size() == 2);
    assert(vec4.size() == 2);

    vec5 = vec3.release();
    assert(vec3.empty());
    assert(vec5.size() == 2);

}

///////////////////////////////////////

void case2()
{
    typedef ptr_vector<string> ptr_vec;
    ptr_vec vec;

    vec.push_back(new string("123"));
    vec.push_back(new string("abc"));
    assert(vec.size() == 2);

    auto pos =
        vec.insert(vec.begin(), new string("000"));
    assert(vec.size() == 3);
    assert(pos == vec.begin());

    ++pos;
    pos = vec.erase(pos);
    assert(vec.size() == 2);
    assert(*pos == "abc");

    auto p =
        vec.replace(pos, new string("xyz"));
    assert(*p == "abc");
    assert(vec.size() == 2);

    ptr_vec vec2;
    vec2 = vec.clone();
    assert(vec.size() == 2);
    assert(vec2.size() == 2);
}

///////////////////////////////////////

int main()
{
    std::cout << "hello reversible_ptr_container" << std::endl;

    case1();
    case2();
}

