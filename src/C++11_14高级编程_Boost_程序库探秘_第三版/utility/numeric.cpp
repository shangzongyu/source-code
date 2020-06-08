// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/core/ignore_unused.hpp>
#include <boost/numeric/conversion/bounds.hpp>
#include <boost/numeric/conversion/cast.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    cout << numeric_limits<short>::min();               //-32768
    cout << numeric_limits<short>::max();               //32767

    cout << numeric_limits<unsigned short>::min();      //0
    cout << numeric_limits<unsigned short>::max();      //65535

    cout << numeric_limits<float>::min();               //1.17549e-38
    cout << numeric_limits<float>::max();               //3.40282e+38

    cout << endl;

    using namespace boost::numeric;

    cout << bounds<short>::lowest();                        //-32768
    cout << bounds<short>::highest();                        //32767;
    cout << bounds<short>::smallest();                  //1

    cout << bounds<float>::lowest();                        //-3.40282e+38
    cout << bounds<float>::highest();                       //3.40282e+38
    cout << bounds<float>::smallest();                  //1.17549e-38

    assert(bounds<short>::lowest()==numeric_limits<short>::min());
    assert(bounds<float>::lowest()==-numeric_limits<float>::max());

    assert(bounds<float>::lowest()==numeric_limits<float>::lowest());

    cout << endl;
}

///////////////////////////////////////

void case2()
{
    using namespace boost::numeric;

    short   s = bounds<short>::highest();
    int     i = numeric_cast<int>(s);
    assert(i == s);

    try
    {
        char c = numeric_cast<char>(s);

        ignore_unused(c);
    }
    catch (std::bad_cast& e)
    {
        cout << e.what() << endl;
    }

}

///////////////////////////////////////

int main()
{
    std::cout << "hello numeric" << std::endl;

    case1();
    case2();
    //case3();
}
