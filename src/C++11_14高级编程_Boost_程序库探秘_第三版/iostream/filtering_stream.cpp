// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/range.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/filter/counter.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/filtering_stream.hpp>

namespace io = boost::iostreams;
using namespace io;
//using namespace boost;

///////////////////////////////////////

void case1()
{
    char ar[10] = "abcd";
    stream<array_source> sa(ar);

    counter ct;
    filtering_istream in;
    assert(in.empty());

    in.push(boost::ref(ct));
    assert(!in.is_complete());
    in.push(sa);
    assert(in.is_complete());

    filtering_ostream out(cout);
    io::copy(in, out);

    assert(ct.characters() == 10);

}

///////////////////////////////////////

int main()
{
    std::cout << "hello iostreams filtering_stream" << std::endl;

    case1();
}
