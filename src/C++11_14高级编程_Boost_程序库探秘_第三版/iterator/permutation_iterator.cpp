// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/iterator/permutation_iterator.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    char s[] = "abcdefg";
    int idx[] = {6, 0, 2, 2, 4};

    std::copy(
        make_permutation_iterator(s, idx),
        make_permutation_iterator(s, idx + 5),
        ostream_iterator<char>(cout, " ")
        );

}

///////////////////////////////////////

int main()
{
    std::cout << "hello permutation_iterator" << std::endl;

    case1();
}


