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
#include <boost/iostreams/filter/counter.hpp>
#include <boost/iostreams/device/back_inserter.hpp>

namespace io = boost::iostreams;
using namespace io;
using namespace boost;

///////////////////////////////////////

class sha1_filter final : public io::multichar_output_filter
{
public:
    typedef char char_type;
    //struct category:
    //    output,
    //    filter_tag,
    //    multichar_tag,
    //    closable_tag
    //    { };
private:
    boost::uuids::detail::sha1 sha;
public:
    sha1_filter() = default;
    ~sha1_filter() = default;
public:

    template<typename Sink>
    std::streamsize write(Sink&, const char_type* s, std::streamsize n)
    {
        sha.process_bytes(s, n);
        return n;
    }

    template<typename Sink>
    void close(Sink& snk)
    {
        unsigned int digest[5];
        sha.get_digest(digest);

        char_type* p = reinterpret_cast<char_type*>(digest);
        io::write(snk, p, sizeof(digest)/sizeof(char_type));
    }
};

BOOST_IOSTREAMS_PIPABLE(sha1_filter, 0);

///////////////////////////////////////

void case1()
{
    char str[] = "The Evil Within";
    string result;

    filtering_ostream out(
        sha1_filter() |
        io::back_inserter(result));

    io::write(out, str, 3);
    assert(result.empty());

    io::write(out, str + 3, 3);
    assert(result.empty());

    io::close(out);
    assert(result.size() == 20);
}

///////////////////////////////////////

template<typename Source, typename Sink>
std::streamsize
copy_no_close_impl(Source src, Sink snk,
              std::streamsize buffer_size ) 
{
    return io::detail::copy_operation<Source, Sink>(
        src , snk, buffer_size )
        ();
}

template<typename Source, typename Sink>
std::streamsize
copy_no_close( const Source& src, Sink& snk,
                  std::streamsize buffer_size =
                     io::default_device_buffer_size
                  BOOST_IOSTREAMS_ENABLE_IF_STREAM(Source)
                  BOOST_IOSTREAMS_ENABLE_IF_STREAM(Sink) ) 
{ 
    return copy_no_close_impl(
        io::detail::wrap(src), 
        io::detail::wrap(snk), 
        buffer_size );
}

void case2()
{
    char str[] = "The Evil Within";
    string result;

    stream<array_source> in(str);

    filtering_ostream out(
        sha1_filter() |
        io::back_inserter(result));

    copy_no_close(in, out);
    assert(in.is_open());

    io::close(in);
    io::close(out);

    assert(result.size() == 20);
}

///////////////////////////////////////

int main()
{
    std::cout << "hello iostreams sha1_filter" << std::endl;

    case1();
    case2();
}

