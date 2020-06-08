// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/iterator/iterator_traits.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    typedef int* I;

    assert((is_same<iterator_value<I>::type, int>::value));
    assert((is_same<iterator_reference<I>::type, int&>::value));
    assert((is_same<iterator_category<I>::type, 
                    std::random_access_iterator_tag>::value));

    typedef list<int>::const_iterator II;

    assert((is_same<iterator_value<II>::type, int>::value));
    assert((is_same<iterator_reference<II>::type,
                     const int&>::value));
    assert((is_same<iterator_category<II>::type, 
                    std::bidirectional_iterator_tag>::value));
}

///////////////////////////////////////

int main()
{
    std::cout << "hello iterator_traits" << std::endl;

    case1();
}
