// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/array.hpp>

namespace io = boost::iostreams;
using namespace io;

int main()
{
    char str[] = "123";
    array_source asrc(str, str + 3);
    stream<array_source> in(asrc);

    char c1, c2, c3;
    in >> c1 >> c2;
    assert(c1 == '1' && c2 == '2');

    in.get(c3);
    assert(c3 == '3' && in.good());
    assert(in.get(c3).eof());

    char str2[10];
    array_sink asnk(str2);
    stream<array_sink> out(asnk);

    out << 'a' << 'b' << 'c';
    assert(str2[0] == 'a' && str2[2] == 'c');
}

