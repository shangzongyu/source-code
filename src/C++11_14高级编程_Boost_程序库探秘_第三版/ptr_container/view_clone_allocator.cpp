// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/assign/ptr_list_of.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_set.hpp>
using namespace boost;

int main()
{
    using namespace boost::assign;

    ptr_vector<int> v = ptr_list_of<int>(100)(1)(10) (2);

    typedef ptr_set<int,std::less<int>, boost::view_clone_allocator> set_view_t;
    set_view_t view(v.begin(), v.end());

    for(auto& i : view)
    {
        cout << i << ",";
    }
    cout << endl;
}

