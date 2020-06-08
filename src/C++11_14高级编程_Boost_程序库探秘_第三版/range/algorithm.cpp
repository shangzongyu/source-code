// Copyright (c) 2016
// Author: Chrono Law
#include <stack>

#include <std.hpp>
using namespace std;

#include <boost/random.hpp>

#include <boost/range.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    vector<int> v{8,1,16,3,7,3,42};

    assert(boost::count(v, 3) == 2);
    assert(boost::find(v, 7) != v.end());

    boost::sort(v);
    assert(boost::adjacent_find(v) != v.end());

}

///////////////////////////////////////

void case2()
{
    vector<int> v(10);
    rand48 rnd;

    boost::sort(
        boost::random_shuffle(
                boost::generate(v, rnd)));

    boost::copy(v, ostream_iterator<int>(cout, " "));

    cout << endl;
}

///////////////////////////////////////

void case3()
{
    vector<int> v{8,1,16,3,7,3,42};

    boost::erase(v,
            boost::remove<return_found_end>(v, 3));

    assert(boost::find(v, 3) == v.end());
    boost::copy(v, ostream_iterator<int>(cout, ","));

}

///////////////////////////////////////

int main()
{
    std::cout << "hello range algorithm" << std::endl;

    case1();
    case2();
    case3();
}


