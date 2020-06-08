// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/random.hpp>
#include <boost/range.hpp>
#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>

namespace io = boost::iostreams;
using namespace io;
using namespace boost;

///////////////////////////////////////

template<typename T = io::source>
class basic_rand_source: public T
{
private:
    std::streamsize  count;
public:
    typedef T super_type;
    typedef typename super_type::char_type char_type;
public:
    basic_rand_source(int c):
        count(c){   }

    std::streamsize read(char_type* s, std::streamsize n)
    {
        using namespace std;

        auto read_count = (min)(n, count);
        if (!read_count)
        {
            return EOF;
        }

        for (streamsize i = 0;i < read_count; ++i)
        {
            *s++ = rand()();
        }

        count -= read_count;
        return read_count;
    }
private:
    typedef variate_generator<rand48, uniform_smallint<>> rand_t;

    static rand_t& rand()
    {
        static rand_t r(rand48(time(0)), uniform_smallint<>('0', 'z'));

        return r;
    }
};

///////////////////////////////////////

void case1()
{
    //typedef std::basic_string<unsigned char> block;

    typedef basic_rand_source<> rand_source;

    string out;
    io::copy(rand_source (20),
        io::back_inserter(out));
    assert(out.size() == 20);

    cout << out << endl;
}

///////////////////////////////////////
#include <boost/range/algorithm.hpp>

void case2()
{
    typedef std::basic_string<unsigned char> block;
    typedef basic_rand_source<io::device<input, unsigned char>> rand_source;

    block out;
    io::copy(rand_source (10),
        io::back_inserter(out));
    assert(out.size() == 10);

    boost::copy(out, ostream_iterator<unsigned char>(cout, " "));
    cout << endl;
}

///////////////////////////////////////

class cout_sink: public io::sink
{
public:
    streamsize write(const char_type* s, streamsize n)
    {
        cout << string(s,n) << endl;
        return n;
    }
};

void case3()
{
    string str("abcd");
    io::copy(
        boost::make_iterator_range(str),
        cout_sink());                             //直接向接收设备输出

}


///////////////////////////////////////

int main()
{
    std::cout << "hello iostreams rand_source" << std::endl;

    case1();
    case2();
    case3();
}
