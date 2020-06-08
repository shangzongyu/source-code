// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/ptr_container/ptr_deque.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    typedef ptr_deque<string> ptr_dq;
    ptr_dq dq;

    assert(dq.empty());

    dq.push_front(new string("mario"));
    dq.push_back(new string("peach"));
    assert(dq[0] == "mario");

    dq.replace(0, new string("luigi"));
    assert(dq.front() == "luigi");

    string** arr = new string*[2];
    arr[0] = new string("123");
    arr[1] = new string("abc");

    dq.transfer(dq.begin(), arr, 2);
    assert(dq.size() == 4);

    string** p = dq.c_array();
    assert(*p[0] == "123" && *p[2] == "luigi");

}

///////////////////////////////////////

int main()
{
    std::cout << "hello ptr_deque" << std::endl;

    case1();
}

