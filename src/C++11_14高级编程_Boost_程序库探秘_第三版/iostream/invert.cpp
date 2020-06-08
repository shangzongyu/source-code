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
#include <boost/iostreams/invert.hpp>
#include <boost/iostreams/device/back_inserter.hpp>

namespace io = boost::iostreams;
using namespace io;
using namespace boost;

///////////////////////////////////////

class null_filter final
{
public:
    typedef char char_type;
    struct category:
        output,
        filter_tag,
        multichar_tag,
        closable_tag
    { };
public:
    template<typename Sink>
    std::streamsize write(Sink& snk, const char_type* s, std::streamsize n)
    {
        io::write(snk, s, n);
        return n;
    }

    template<typename Sink>
    void close(Sink& snk)
    {}
};
BOOST_IOSTREAMS_PIPABLE(null_filter, 0);
BOOST_IOSTREAMS_PIPABLE(inverse, 1);

int main()
{
    char str[] = "Ground Zero";
    string result;

    filtering_istream in(
        invert(null_filter()) |
        array_source(str));

    io::copy(in, io::back_inserter(result));

    //cout << result << endl;
}

