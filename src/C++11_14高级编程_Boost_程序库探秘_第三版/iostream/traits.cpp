// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

//#include <boost/type_traits.hpp>

#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/filter/counter.hpp>
#include <boost/iostreams/traits.hpp>

namespace io = boost::iostreams;
using namespace io;

///////////////////////////////////////

void case1()
{
    assert((is_same<char_type_of<array_source>::type, char>::value));
    assert((is_same<char_type_of<array_sink>::type  , char>::value));

    assert((is_same<char_type_of<warray_source>::type, wchar_t>::value));
    assert((!is_same<char_type_of<warray_sink>::type,
                      char_type_of<array_sink>::type>::value));
}

///////////////////////////////////////

void case2()
{
    assert((is_same<mode_of<array_source>::type, input_seekable>::value));
    assert((is_same<mode_of<array_sink>::type, output_seekable>::value));

    assert((is_same<mode_of<io::array>::type, seekable>::value));
}

///////////////////////////////////////

void case3()
{
    assert((is_convertible<category_of<array_source>::type,
                input_seekable>::value));
    assert((is_convertible<category_of<array_source>::type,
                device_tag>::value));

    assert((is_convertible<category_of<counter>::type, filter_tag>::value));
    assert((is_convertible<category_of<counter>::type, dual_use>::value));

}

///////////////////////////////////////

int main()
{
    std::cout << "hello iostreams traits" << std::endl;

    case1();
    case2();
    case3();
}


