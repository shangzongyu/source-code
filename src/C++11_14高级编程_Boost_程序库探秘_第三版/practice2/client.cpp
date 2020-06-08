// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/asio.hpp>
using namespace boost;
using namespace boost::asio;

int main()
{
    cout << "client start" << endl;

    io_service ios;
    ip::tcp::socket sock(ios);

    ip::tcp::endpoint ep(
        ip::address::from_string("127.0.0.1"), 6677);
    sock.connect(ep);

    string str("hello world");
    sock.write_some(buffer(str));

    vector<char> v(100, 0);
    size_t n = sock.read_some(buffer(v));
    cout << "recv "<< n << " :" << v.data() << endl;
};

