// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

// typedef decltype(nullptr) nullptr_t;

///////////////////////////////////////

void case1()
{
    int* p1 = nullptr;
    vector<int>* p2 = nullptr;

    assert(!p1 && !p2);
    assert(p1 == nullptr);

    //assert(10 >= nullptr);

    nullptr_t nil;

    double* p3 = nil;
    assert(nil == nullptr);
    assert(!p3);
}

///////////////////////////////////////

int main()
{
    std::cout << "hello C++11/14 nullptr" << std::endl;

    case1();
}

