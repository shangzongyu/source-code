// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/range.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/combine.hpp>

namespace io = boost::iostreams;
using namespace io;
//using namespace boost;

///////////////////////////////////////

void case1()
{
    char src[] = "12345678";
    string result;

    typedef io::combination<array_source,
            back_insert_device<string> > bi_dev;

    assert(is_device<bi_dev>::value);
    assert((std::is_same<
            mode_of<bi_dev>::type, bidirectional
            >::value));

    bi_dev dev = io::combine(
        array_source(src),
        io::back_inserter(result));

    io::write(dev, src, 2);
    assert(result.size() == 2);

}

///////////////////////////////////////

int main()
{
    std::cout << "hello iostreams combine" << std::endl;

    case1();
}
