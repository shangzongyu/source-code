// Copyright (c) 2016
// Author: Chrono Law
#include <stack>

#include <std.hpp>
using namespace std;

#include <boost/array.hpp>
#include <boost/range.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    assert(has_range_iterator<vector<int>>::value);
    assert(has_range_iterator<string>::value);
    assert(!has_range_iterator<stack<int>>::value);

    typedef boost::array<char, 5> array_t;
    assert(has_range_iterator<array_t>::value);

    typedef pair<int*,int*> pair_t;
    assert(has_range_iterator<pair_t>::value);

    char a[] = "range";
    assert(has_range_iterator<decltype(a)>::value);

    assert(!has_range_iterator<char*>::value);

}

///////////////////////////////////////

int main()
{
    std::cout << "hello range traits" << std::endl;

    case1();
}

