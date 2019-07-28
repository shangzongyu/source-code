// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/range.hpp>
#include <boost/iostreams/filter/regex.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/compose.hpp>

namespace io = boost::iostreams;
using namespace io;
using namespace boost;

///////////////////////////////////////

int main()
{
    std::cout << "hello iostreams compose" << std::endl;

    string str("abcdef aochijk");

    io::copy(
        boost::make_iterator_range(str),
        compose(regex_filter(regex("a.c"), "test"),
                cout)
        );

}
