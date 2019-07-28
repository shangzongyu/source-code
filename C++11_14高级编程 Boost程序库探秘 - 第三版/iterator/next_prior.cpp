// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/next_prior.hpp>
//using namespace boost;

///////////////////////////////////////

template<typename I>
typename iterator_traits<I>::value_type
get_n(I& iter, int n)
{
    return *(boost::next(iter, n));
}

void case1()
{
    list<int> l{1,2,3,4};

    auto p1 = l.begin();
    auto p2 = l.end();

    assert(get_n(p1, 1)     == 2);
    assert(get_n(p2, -1)    == 4);
    assert(get_n(p2, -2)    == 3);

}

///////////////////////////////////////

int main()
{
    std::cout << "hello next_prior" << std::endl;

    case1();
}
