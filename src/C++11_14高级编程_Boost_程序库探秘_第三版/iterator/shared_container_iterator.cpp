// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/shared_container_iterator.hpp>
#include <boost/make_shared.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    auto sv = boost::make_shared<vector<int>>(10);

    typedef shared_container_iterator<vector<int> > sci_t;

    sci_t first(sv->begin(), sv);
    sci_t last (sv->end()  , sv);

    std::fill(first, last, 9);

    std::fill(
            make_shared_container_iterator(sv->begin(), sv),
            make_shared_container_iterator(sv->end()  ,sv),
            9);

}

///////////////////////////////////////

int main()
{
    std::cout << "hello shared_container_iterator" << std::endl;

    case1();
}
