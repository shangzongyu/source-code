// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/ptr_container/ptr_array.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    typedef ptr_array<string, 5> ptr_arr;
    ptr_arr arr;

    assert(!arr.empty());
    assert(arr.size() == 5 && arr.max_size() == 5);
    assert(arr.base().front() == nullptr);

    arr.replace(0, new string("metroid"));
    arr.replace<2>(new string("prime"));
    arr.replace<4>(new string("other m"));
    assert(arr.front() == "metroid");
    assert(arr.back() == "other m");

    arr[0] = "samus";
    arr.at<2>() = "alan";

    assert(*boost::next(arr.begin(), 2) == "alan");

}

///////////////////////////////////////

int main()
{
    std::cout << "hello ptr_array" << std::endl;

    case1();
}



