// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/range.hpp>
#include <boost/iostreams/device/null.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/regex.hpp>
#include <boost/iostreams/filter/grep.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>

namespace io = boost::iostreams;
using namespace io;
using namespace boost;

///////////////////////////////////////

void case1()
{
    regex reg("a.c");
    string str("abcdef aochijk");
    string result;

    filtering_ostream out(
        regex_filter(reg, "test") |
        io::back_inserter(result));

    io::copy(
        boost::make_iterator_range(str),
        out);

    cout << result << endl;

}

///////////////////////////////////////

string reg_format(const match_results<const char*>& match)
{
    return string("test-") + match[1] + "-";
}


void case2()
{
    regex reg("a(.)c");
    string str("abcdef aochijk");
    string result;

    auto formatter = [](const regex_filter::match_type& match)
                  {
                      return string("test-") + match[1] + "-";
                  };
    filtering_ostream out(
            //regex_filter(reg, reg_format)|
            regex_filter(reg, formatter) |
            io::back_inserter(result));

    io::copy(
        boost::make_iterator_range(str),
        out);
    cout << result << endl;

}

///////////////////////////////////////

void case3()
{
    regex reg("a.c");
    string str( "abcdef\n"
                "12345\n"
                "aochijk\n");
    string result;

    //filtering_ostream out(
    //        grep_filter(reg) |
    //        io::back_inserter(result));

    filtering_ostream out(
          grep_filter(reg,  regex_constants::match_default, grep::invert) |
          io::back_inserter(result));


    io::copy(
        boost::make_iterator_range(str),
        out);
    cout << result << endl;

}

///////////////////////////////////////

int main()
{
    std::cout << "hello iostreams regex" << std::endl;

    case1();
    case2();
    case3();
}
