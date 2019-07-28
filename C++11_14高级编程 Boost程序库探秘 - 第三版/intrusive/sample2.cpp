// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/next_prior.hpp>
#include <boost/intrusive/slist.hpp>
using namespace boost::intrusive;


///////////////////////////////////////

class point: public slist_base_hook<>
{
public: 
    int x,y;
    point(int a = 0, int b = 0):
        x(a), y(b){}
};

///////////////////////////////////////

void case1()
{
    point p1, p2(2,2), p3(3,3);

    //slist<point> sl;
    slist<point, cache_last<true> > sl;

    sl.push_front(p1);
    sl.push_front(p2);
    sl.push_front(p3);

    assert(sl.size() == 3);
    sl.reverse();

    for(auto& p : sl)
    {
        cout << p.x << "-" << p.y << " ";
    }

    sl.erase(boost::next(sl.begin()));

}

///////////////////////////////////////

int main()
{
    std::cout << "hello intrusive sample2" << std::endl;

    case1();
}
