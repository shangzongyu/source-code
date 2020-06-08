// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/range.hpp>
#include <boost/iostreams/device/null.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/null.hpp>
#include <boost/iostreams/filter/counter.hpp>
#include <boost/iostreams/filtering_stream.hpp>


namespace io = boost::iostreams;
using namespace io;
using namespace boost;

///////////////////////////////////////

void case1()
{
    string str("counter\nfilter\n");

    filtering_ostream out(counter() | null_sink() ); 

    io::copy(
        boost::make_iterator_range(str), out );

    auto pc = out.component<counter>(0);
    assert(pc->characters() == 15);
    assert(pc->lines() == 2);

}

///////////////////////////////////////

int main()
{
    std::cout << "hello iostreams counter" << std::endl;

    case1();
}

