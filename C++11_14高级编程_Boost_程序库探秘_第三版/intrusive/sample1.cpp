// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/noncopyable.hpp>

///////////////////////////////////////

class point: boost::noncopyable
{
public:
    int x,y;

    typedef point*  node_ptr;
    node_ptr        next;

    point(int a = 0, int b = 0):
        x(a), y(b), next(nullptr){}

    node_ptr get_next()
    {   return next;}

    void set_next(node_ptr p)
    {   next = p;}
};

///////////////////////////////////////

void case1()
{
    point p1, p2(2,2), p3(3,3);

    p1.set_next(&p2);
    p2.set_next(&p3);

    for (point::node_ptr p = &p1;
         p != nullptr;
         p = p->get_next())
    {
        cout << p->x << "-" << p->y << " ";
    }

    p1.set_next(&p3);

}

///////////////////////////////////////

int main()
{
    std::cout << "hello intrusive sample1" << std::endl;

    case1();
}
