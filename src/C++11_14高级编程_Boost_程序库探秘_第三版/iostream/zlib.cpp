// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/range.hpp>
#include <boost/iostreams/device/null.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>

namespace io = boost::iostreams;
using namespace io;
using namespace boost;

///////////////////////////////////////

void case1()
{
    string str("12345678 12345678");
    string zip_str, unzip_str;

    filtering_ostream zout(
        zlib_compressor() | io::back_inserter(zip_str) );

    io::copy(
        boost::make_iterator_range(str),
        zout);

    filtering_ostream uzout(
        zlib_decompressor() | io::back_inserter(unzip_str) );

    io::copy(
        boost::make_iterator_range(zip_str),
        uzout);

    assert(unzip_str == str);

}

///////////////////////////////////////

int main()
{
    std::cout << "hello iostreams zlib" << std::endl;

    case1();
}
