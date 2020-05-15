// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/next_prior.hpp>
#include <boost/foreach.hpp>

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/assign/ptr_list_of.hpp>
#include <boost/intrusive/slist.hpp>

using namespace boost::intrusive;
using namespace boost;

///////////////////////////////////////

class point final
{
public:
    int x,y;
    point(int a = 0, int b = 0):
        x(a), y(b){}

    slist_member_hook<> m_hook;
};

///////////////////////////////////////

void case1()
{
    using namespace boost::assign;

    ptr_vector<point> vec =
        ptr_list_of<point>()(2,2)(3,3);

    typedef member_hook<point, slist_member_hook<>,
        &point::m_hook> member_option;
    slist<point, member_option> sl;

    BOOST_REVERSE_FOREACH(auto& p, vec)
    {
        sl.push_front(p);
    }
    assert(sl.size() == 3);

    for(point& p : sl)
    {
        cout << p.x << "-" << p.y << " ";
    }

    sl.clear();
}

///////////////////////////////////////

int main()
{
    std::cout << "hello intrusive sample3" << std::endl;

    case1();
}
