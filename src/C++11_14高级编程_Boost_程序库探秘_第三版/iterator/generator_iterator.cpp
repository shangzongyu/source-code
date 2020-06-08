// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/generator_iterator.hpp>
#include <boost/random.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    boost::rand48 rng;

    auto iter = make_generator_iterator(rng);

    for (int i = 0;i < 5; ++i)
    {
        cout << *++iter << ",";
    }

}

///////////////////////////////////////

int main()
{
    std::cout << "hello generator_iterator" << std::endl;

    case1();
}

