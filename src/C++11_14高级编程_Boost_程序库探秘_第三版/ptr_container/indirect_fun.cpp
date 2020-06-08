// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/smart_ptr.hpp>
#include <boost/ptr_container/indirect_fun.hpp>
using namespace boost;

int main()
{
    std::cout << "hello indirect_fun" << std::endl;

    typedef boost::shared_ptr<string> ptr_string;

    ptr_string s1(new string("chrono"));
    ptr_string s2(new string("trigger"));

    assert(indirect_fun<not_equal_to<string> >()(s1, s2));
    cout << indirect_fun<std::plus<string> >()(s1, s2) << endl;

    void* p1 = s1.get();
    void* p2 = s2.get();

    assert((void_ptr_indirect_fun<less<string>, string >()(p1, p2)));
}

