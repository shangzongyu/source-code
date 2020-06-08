// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/range.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/null.hpp>
#include <boost/iostreams/filter/newline.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>

namespace io = boost::iostreams;
using namespace io;
using namespace boost;

///////////////////////////////////////

void case1()
{
    string str( "abcdef\n"
            "12345\n"
            "aochijk\n");
    string result;

    filtering_ostream out(
            newline_filter(newline::mac) |
            io::back_inserter(result));

    io::copy(boost::make_iterator_range(str),
            out);
    cout << result << endl;

}

///////////////////////////////////////

void case2()
{
    string str( "abcdef\n"
            "12345\n"
            "aochijk\n");

    filtering_ostream out(
            newline_checker() | io::null_sink()); 

    io::copy(boost::make_iterator_range(str), out); 
    assert(out.component<newline_checker>(0)->is_posix());

}

///////////////////////////////////////

int main()
{
    std::cout << "hello iostreams newline" << std::endl;

    case1();
    case2();
}


