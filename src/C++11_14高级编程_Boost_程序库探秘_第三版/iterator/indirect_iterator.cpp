// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/checked_delete.hpp>
#include <boost/iterator/indirect_iterator.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    vector<int*> v = {new int(1), new int(2)};

    for (auto pos = v.begin(); pos != v.end(); ++pos) 
    {
        cout << **pos << ",";
    }
    cout << endl;

    for (auto& x : v)
    {
        cout << *x << ",";
    }
    cout << endl;

    auto start  = make_indirect_iterator(v.begin());
    auto finish = make_indirect_iterator(v.end());
    for(;start != finish;)
    {
        cout << *start++ << ",";
    }

    for_each(v.begin(), v.end(), checked_deleter<int>());

}

///////////////////////////////////////

int main()
{
    std::cout << "hello indirect_iterator" << std::endl;

    case1();
}



