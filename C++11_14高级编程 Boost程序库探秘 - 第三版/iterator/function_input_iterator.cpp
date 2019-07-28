// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/random.hpp>
#include <boost/iterator/function_input_iterator.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    rand48 rng;

    std::copy(
            make_function_input_iterator(rng, 0),
            make_function_input_iterator(rng, 5),
            ostream_iterator<int>(cout, "\n")
            );

    vector<int> v(10);

    std::copy(
            make_function_input_iterator(rng, v.begin()),
            make_function_input_iterator(rng, v.end()),
            v.begin()   );

}

///////////////////////////////////////

int main()
{
    std::cout << "hello function_input_iterator" << std::endl;

    case1();
}
