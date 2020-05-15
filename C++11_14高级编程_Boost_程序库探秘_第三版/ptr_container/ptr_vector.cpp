// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/ptr_container/ptr_vector.hpp>
using namespace boost;

///////////////////////////////////////


int main()
{
    std::cout << "hello ptr_vector" << std::endl;

    typedef ptr_vector<string> ptr_vec;
    ptr_vec vec(10);

    assert(vec.empty());
    assert(vec.capacity() == 10);

    vec.push_back(new string("star"));
    assert(vec[0] == "star");

    vec.replace(0, new string("fox"));
    assert(vec[0] == "fox");

    auto arr = new string*[2];
    arr[0] = new string("123");
    arr[1] = new string("abc");

    vec.transfer(vec.begin(), arr, 2);
    assert(vec.size() == 3);

    auto p = vec.c_array();
    assert(*p[0] == "123" && *p[2] == "fox");

}
