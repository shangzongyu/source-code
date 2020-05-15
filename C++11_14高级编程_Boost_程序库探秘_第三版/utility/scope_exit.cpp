// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
//using namespace std;

#include <boost/scope_exit.hpp>

///////////////////////////////////////

void case1()
{
    int *p = new int[100];

    BOOST_SCOPE_EXIT((p))
    {
        std::cout << "scope exit called." << std::endl;
        delete[] p;
        std::cout << "scope exit end." << std::endl;
    }BOOST_SCOPE_EXIT_END

    std::cout << "ok. scope exit." << std::endl;
}

///////////////////////////////////////

#include <boost/smart_ptr.hpp>
using namespace boost;

void case2()
{
    int *p = new int[100];

    shared_ptr<void> x(nullptr, [&](void*)
        {
            std::cout << "lambda exit called." << std::endl;
            delete[] p;
            std::cout << "lambda exit end." << std::endl;
        }
    );

    std::cout << "ok. lambda exit." << std::endl;
}

///////////////////////////////////////

int main()
{
    std::cout << "hello scope_exit" << std::endl;

    case1();
    case2();
}
