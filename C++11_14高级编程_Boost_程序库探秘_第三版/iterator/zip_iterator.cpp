// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/tuple/tuple.hpp>
#include <boost/function_output_iterator.hpp>

#include <boost/iterator/zip_iterator.hpp>
using namespace boost;

#include "step_iterator.hpp"

///////////////////////////////////////

class to_hex2
{
private:
    vector<unsigned char> &v;
    char trans(const char c) const
    {
        if (c >= 'a')
        {   return c - 'a' + 10;}
        else if (c >= 'A')
        {   return c - 'A' + 10;}
        else
        {   return c - '0';}
    }
public:
    to_hex2(vector<unsigned char> &_v):
      v(_v){}

    typedef boost::tuple<const char&, const char& > Tuple;
    void operator()(Tuple const& t) const
    {
          static char tmp;
          tmp = trans(get<0>(t))* 0x10;
          tmp += trans(get<1>(t));
          v.push_back(tmp);
    }
};

void case1()
{
    char s[] = "1234aBcD";
    vector<unsigned char> v;

    typedef step_iterator<const char*> si_t;

    for_each(
            make_zip_iterator(
                boost::make_tuple(si_t(s), si_t(s + 1))),
            make_zip_iterator(
                boost::make_tuple(si_t(s + 8), si_t(s + 9))),
            to_hex2(v)
            );

    assert(v.size() == 4);

    std::copy(
            make_zip_iterator(
                boost::make_tuple(si_t(s), si_t(s + 1))),
            make_zip_iterator(
                boost::make_tuple(si_t(s + 8), si_t(s + 9))),
            make_function_output_iterator(to_hex2(v))
            );

}

///////////////////////////////////////

int main()
{
    std::cout << "hello zip_iterator" << std::endl;

    case1();
}



