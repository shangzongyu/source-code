// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/assign/ptr_list_inserter.hpp>
#include <boost/assign/ptr_map_inserter.hpp>

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_deque.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/ptr_container/ptr_set.hpp>
#include <boost/ptr_container/ptr_map.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    using namespace boost::assign;

    ptr_vector<int> v;
    ptr_push_back(v)()(1)(2)(100);
    assert(v.size() == 4);

    ptr_list<complex<double> > lt;
    ptr_push_front(lt)(1, 2)(0.618, 1.732);
    ptr_push_back<complex<double>>(lt)(2.718, 3.14);
    assert(lt.size() == 3);

    ptr_multimap<int, string> m;
    ptr_map_insert(m)(1, "one")(1, "neo");
    assert(m.size() == 2);

}

///////////////////////////////////////
#include <boost/assign/ptr_list_of.hpp>

void case2()
{
    using namespace boost::assign;

    ptr_vector<int> v = ptr_list_of<int>()(1)(2);

    ptr_deque<complex<double> > dq =
        ptr_list_of<complex<double>>(1, 2)(0.618, 1.732);

    ptr_set<string> s ;
    s = ptr_list_of<string>()("abc") ("xyz").to_container(s);
}


///////////////////////////////////////

int main()
{
    std::cout << "hello ptr_unordered_set" << std::endl;

    case1();
    case2();
}

