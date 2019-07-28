// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/algorithm/hex.hpp>
#include <boost/range.hpp>

#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/counter.hpp>
#include <boost/iostreams/filter/aggregate.hpp>
#include <boost/iostreams/device/back_inserter.hpp>

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

int main()
{
    char str[] = "313";
    string result;

    filtering_ostream out(
        hex_filter() |
        counter() |
        io::back_inserter(result));

    io::copy(array_source(str, str + 3), out);

    cout << result << endl;
    assert(result.size() == 6);
    assert(out.component<counter>(1)->characters() == 6);
}

