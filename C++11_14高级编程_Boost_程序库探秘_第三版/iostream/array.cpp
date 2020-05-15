// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/array.hpp>

namespace io = boost::iostreams;
using namespace io;


///////////////////////////////////////

void case1()
{
    char buf[] = "123";
    array_source as1(buf, buf + 3);
    array_source as2(buf);

    assert(as1.input_sequence().first == buf);
    assert(as1.input_sequence().second == buf + 3);
    assert(as2.input_sequence().second == buf + 4);

    int buf1[10] = {1, 2, 3}, buf2[10];
    basic_array_source<int> ai(buf1);
    basic_array<int> ar(buf2);

    stream<basic_array_source<int> > in(ai);
    stream<basic_array<int> > out(ar);

    io::copy(in, out);

}

///////////////////////////////////////

int main()
{
    std::cout << "hello iostreams array" << std::endl;

    case1();
}
