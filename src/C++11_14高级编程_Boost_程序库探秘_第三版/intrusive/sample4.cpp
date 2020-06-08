// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/next_prior.hpp>
#include <boost/intrusive/slist.hpp>
using namespace boost::intrusive;

///////////////////////////////////////

void case1()
{
    typedef slist_node<void*>       node_t;
    typedef slist_node_traits<void*>    node_traits_t;
    typedef circular_slist_algorithms<node_traits_t> algo;

    node_t n1, n2;

    algo::init_header(&n1);
    assert(algo::count(&n1) == 1);

    algo::link_after(&n1, &n2);
    assert(algo::count(&n1) == 2);

    algo::unlink(&n1);
    assert(algo::count(&n2) == 1);

}

///////////////////////////////////////

int main()
{
    std::cout << "hello intrusive sample4" << std::endl;

    case1();
}
