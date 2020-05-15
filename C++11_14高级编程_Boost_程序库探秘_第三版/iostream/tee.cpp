// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/algorithm/hex.hpp>
#include <boost/range.hpp>

#include <boost/iostreams/filter/regex.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/aggregate.hpp>
#include <boost/iostreams/device/null.hpp>
#include <boost/iostreams/compose.hpp>
#include <boost/iostreams/tee.hpp>

namespace io = boost::iostreams;
using namespace io;
using namespace boost;

///////////////////////////////////////

class hex_filter final:
    public io::aggregate_filter<char>
{
private:
  typedef io::aggregate_filter<char>  super_type;
  typedef super_type::vector_type     vector_type;

  virtual void do_filter(const vector_type& src, vector_type& dest)
  {
      boost::algorithm::hex(src, std::back_inserter(dest));
  }
};

BOOST_IOSTREAMS_PIPABLE(hex_filter, 0)

///////////////////////////////////////

void case1()
{
    string str("abcdef aochijk");
    string result;

    filtering_ostream out(
            tee(
                compose(regex_filter(regex("a.c"), "test"), cout),
                compose(hex_filter(), io::back_inserter(result))
                )
        );

    io::copy(
        boost::make_iterator_range(str),
        out);

    cout << endl << result << endl;
}


///////////////////////////////////////

int main()
{
    std::cout << "hello iostreams tee" << std::endl;

    case1();
}

