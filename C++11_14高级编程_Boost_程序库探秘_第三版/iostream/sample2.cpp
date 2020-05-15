// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/counter.hpp>

namespace io = boost::iostreams;
using namespace io;

int main()
{
    char arr[] = "12345678";
    stream<array_source> in(arr, arr + 8);

    string str;
    filtering_ostream out(
        counter() |
        io::back_inserter(str));

    io::copy(in, out);
    assert(str.size() == 8);
    assert(str == arr);
    assert(out.component<counter>(0)->characters() == 8);
}

