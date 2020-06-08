// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/ptr_container/ptr_circular_buffer.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    typedef ptr_circular_buffer<string> ptr_buffer;
    ptr_buffer cb(5);

    assert(cb.empty());

    cb.push_front(new string("link"));
    cb.push_back(new string("zelda"));
    cb.push_back(new string("epona"));

    assert(cb.size() == 3);
    assert(!cb.full());
    assert(cb[1] == "zelda");

    string** p = cb.linearize();
    assert(*p[0] == "link");

    cb.rotate( boost::prior(cb.end()) );
    assert(*cb.c_array()[0] == "epona");

}

///////////////////////////////////////

int main()
{
    std::cout << "hello ptr_circular_buffer" << std::endl;

    case1();
}



