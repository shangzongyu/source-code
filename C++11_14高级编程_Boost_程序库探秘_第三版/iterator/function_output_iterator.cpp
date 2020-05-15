// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/random.hpp>
#include <boost/function_output_iterator.hpp>
using namespace boost;

///////////////////////////////////////

class to_hex
{
private:
    vector<unsigned char> &v;
    int count;

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
    to_hex(vector<unsigned char> &_v):
        v(_v), count(0){}

    void operator()(const char c) 
    {
        static char tmp;
        if ((count++) % 2 == 0)
        {
            tmp = trans(c)* 0x10;
        }
        else
        {
            tmp += trans(c);
            v.push_back(tmp);
        }
    }
};

void case1()
{
    char s[] = "1234abcd";

    vector<unsigned char> v;
    to_hex h(v);
    function_output_iterator<to_hex> foi(h);

    //std::copy(s, s + 8, foi);
    std::copy(s, s + 8,
        make_function_output_iterator(to_hex(v)));

    assert(v.size() == 4);

}

///////////////////////////////////////

int main()
{
    std::cout << "hello function_output_iterator" << std::endl;

    case1();
}

