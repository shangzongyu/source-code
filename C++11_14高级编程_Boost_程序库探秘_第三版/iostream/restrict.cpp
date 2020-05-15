// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/uuid/sha1.hpp>

#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/counter.hpp>
#include <boost/iostreams/restrict.hpp>
#include <boost/iostreams/device/back_inserter.hpp>

namespace io = boost::iostreams;
using namespace io;
using namespace boost;

///////////////////////////////////////

BOOST_IOSTREAMS_PIPABLE(restriction, 1);

int main()
{
    char str[] = "1234";
    string result;

    filtering_istream in(
        restrict(counter(),1,2) |
        array_source(str));

    io::copy(in, io::back_inserter(result));
    assert(result == "23");
}

