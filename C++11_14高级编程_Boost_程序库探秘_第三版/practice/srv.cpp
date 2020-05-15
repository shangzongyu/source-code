// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include "tcp_server.hpp"

int main()
{
    cout << "server start" << endl;

    tcp_server svr(6677);
    svr.run();
}

