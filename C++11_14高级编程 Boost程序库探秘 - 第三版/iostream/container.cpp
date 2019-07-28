// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/range.hpp>

#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/copy.hpp>

namespace io = boost::iostreams;
using namespace io;
using namespace boost;

///////////////////////////////////////

void case1()
{
    string str("123");
    filtering_istream in(make_iterator_range(str));

    vector<char> v(str.begin(), str.end());
    filtering_istream in2(make_iterator_range(v));

}

///////////////////////////////////////

#include <boost/iostreams/device/back_inserter.hpp>

void case2()
{
    string str("123");
    vector<char> v;

    io::copy( make_iterator_range(str),
              io::back_inserter(v));

}

///////////////////////////////////////

int main()
{
    std::cout << "hello iostreams container" << std::endl;

    case1();
    case2();
}
