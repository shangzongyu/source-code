// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/random.hpp>
#include <boost/iterator/counting_iterator.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    counting_iterator<int> i(100);

    assert(*i++ == 100);
    assert(*i == 101);
    assert(*++i == 102);

    vector<int> v;
    std::copy(
        make_counting_iterator(0),
        make_counting_iterator(10),
        back_inserter(v)
        );
}

///////////////////////////////////////

template<typename R>
class rand_int
{
private:
    R &r;
    int count;
public:
    rand_int(R& _r, int c = 0):
        r(_r), count(c) {}
    rand_int(rand_int const &other) = default;
    rand_int& operator=(rand_int const &other) = default;

    void operator++()
    {   ++count;}

    friend bool operator==(rand_int const &l, rand_int const &r)
    {   return l.count == r.count;}

    operator typename R::result_type () const
    {   return r(); }
};

void case2()
{
    typedef counting_iterator<rand_int<rand48>,
        boost::single_pass_traversal_tag, int> RandIter;

    boost::rand48 r;

    rand_int<rand48> r1(r, 0), r2(r, 10);
    RandIter first(r1), last(r2);

    vector<int> v;
    std::copy(first, last, back_inserter(v));
    assert(v.size() == 10);

}

///////////////////////////////////////

int main()
{
    std::cout << "hello counting_iterator" << std::endl;

    case1();
    case2();
}




