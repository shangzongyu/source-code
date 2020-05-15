// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/counter.hpp>
#include <boost/iostreams/filter/line.hpp>
#include <boost/iostreams/device/back_inserter.hpp>

namespace io = boost::iostreams;
using namespace io;
using namespace boost;

///////////////////////////////////////

class bracket_line_filter final:
    public io::basic_line_filter<char>
{
private:
    typedef io::basic_line_filter<char>     super_type;
    typedef typename super_type::string_type    string_type;

    virtual string_type do_filter(const string_type& line)
    {
        return "<" + line + ">";
    }
};

BOOST_IOSTREAMS_PIPABLE(bracket_line_filter, 0);

///////////////////////////////////////

int main()
{
    string str("The\nPhantom\nPain");

    filtering_istream in(
            bracket_line_filter() |
            boost::make_iterator_range(str));
    io::copy(in, cout);
}

