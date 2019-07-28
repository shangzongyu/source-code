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

    assert(!vec.empty());
    assert(vec.size() == 2);

    assert(vec[0] == "123");
    vec.back() = "def";
    assert(vec[1] == "def");

    auto iter = vec.begin();
    assert(iter->length() == 3);

    vec.clear();
    assert(vec.empty());

}

///////////////////////////////////////

void case2()
{
    vector<string*> vec;
    vec.push_back(new string("123"));
    vec.push_back(new string("123"));

    assert(*vec[0] == "123");
    *vec.back() = "def";
    assert(*vec[1] == "def");

    auto iter = vec.begin();
    assert((*iter)->length() == 3);

}

///////////////////////////////////////

void case3()
{
    typedef ptr_vector<string> ptr_vec;
    ptr_vec vec;

    auto_ptr<string> ap(new string("123"));
    vec.push_back(ap);
    assert(ap.get() == 0);

    vec.push_back(auto_ptr<string>(new string("abc")));
    vec.push_back(new string("xyz"));
    assert(vec.size() == 3); 

    ptr_vec::auto_type p =
        vec.release(vec.begin());
    assert(vec.size() == 2);
    assert(p && *p == "123");

    string* sp = p.release();
    assert(!p);
    delete sp;

    ptr_vec vec2;

    vec2.transfer(vec2.end(),vec);
    assert(vec.empty());
    assert(vec2.size() == 2);

}

///////////////////////////////////////

int main()
{
    std::cout << "hello ptr sample" << std::endl;

    case1();
    case2();
    case3();
}
