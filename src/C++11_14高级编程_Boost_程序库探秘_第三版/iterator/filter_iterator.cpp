// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/iterator/counting_iterator.hpp>

#include <boost/iterator/filter_iterator.hpp>
using namespace boost;

///////////////////////////////////////

bool is_prime(int x)
{
    for (int i = 2; i < x / 2; ++i)
    {
        if (x % i == 0)
        {   return false;}
    }
    return true;
}

#include "step_iterator.hpp"

void case1()
{
    typedef counting_iterator<int> ci_t;
    ci_t c1(11), c2(101);

    typedef step_iterator<ci_t> si_t;
    si_t si1(c1), si2(c2);

    //typedef filter_iterator<bool(*)(int), si_t> fi_t;
    typedef filter_iterator<decltype(&is_prime), si_t> fi_t;

    fi_t first(&is_prime, si1, si2);
    fi_t last(&is_prime, si2, si2);

    //std::copy(first, last,
    //    ostream_iterator<int>(cout, " "));

    std::copy(
            make_filter_iterator(&is_prime, si1, si2),
            make_filter_iterator(&is_prime, si2, si2),
            ostream_iterator<int>(cout, " "));

}

///////////////////////////////////////

int main()
{
    std::cout << "hello filter_iterator" << std::endl;

    case1();
}

