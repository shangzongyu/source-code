// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/range.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/copy.hpp>

namespace io = boost::iostreams;
using namespace io;
using namespace boost;

///////////////////////////////////////

void case1()
{
    string str("file device");
    file_sink fsink("test.txt");

    io::copy(
        make_iterator_range(str),
        fsink);

    file_source fsrc("test.txt");
    io::copy(fsrc, cout);

}

///////////////////////////////////////

int main()
{
    std::cout << "hello iostreams file" << std::endl;

    case1();
}

