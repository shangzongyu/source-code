// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/ptr_container/ptr_deque.hpp>
#include <boost/ptr_container/ptr_list.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    typedef ptr_list<string> ptr_lt;
    ptr_lt lt;

    lt.push_front(new string("mario"));
    lt.push_back(new string("peach"));
    lt.insert(lt.end(), new string("yoshi"));
    assert(lt.size() == 3);

    ptr_deque<string> dq(lt.begin(), std::next(lt.begin(), 2));
    assert(dq.size() == 2);
    assert(lt.size() == 3);

}

///////////////////////////////////////

int main()
{
    std::cout << "hello ptr_list" << std::endl;

    case1();
}


