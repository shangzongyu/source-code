// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/iterator/iterator_facade.hpp>
using namespace boost;

///////////////////////////////////////

template<typename T>
class vs_iterator :
        public boost::iterator_facade<
        vs_iterator<T>, T,
        boost::single_pass_traversal_tag>
{
public:
    typedef boost::iterator_facade<
        vs_iterator<T>, T,boost::single_pass_traversal_tag> super_type;
    typedef vs_iterator this_type;

    typedef typename super_type::reference reference;
    // using typename super_type::reference ;

private:
    std::vector<T> &v;
    size_t current_pos;
public:
    vs_iterator(vector<T> &_v, size_t pos = 0):
      v(_v), current_pos(pos)
    {}
    vs_iterator(this_type const& other):
        v(other.v), current_pos(other.current_pos)
    {}
    void operator=(this_type const& other)
    {
        this->v = other.v;
        this->current_pos = other.current_pos;
    }
private:
    friend class boost::iterator_core_access;

    reference dereference() const
    {   return v[current_pos]; }

    void increment()
    {   ++current_pos;  }

    bool equal(this_type const& other) const
    {   return this->current_pos == other.current_pos;}
};

void case1()
{
    vector<int> v{1,2,3,4,5};

    vs_iterator<int> vsi(v), vsi_end(v, v.size());
    *vsi = 9;

    std::copy(vsi, vsi_end,
            ostream_iterator<int>(cout, ","));

    cout << endl;
}

///////////////////////////////////////

#include "step_iterator.hpp"

void case2()
{
    char s[] = "12345678";
    std::copy(s, s + 8,
            std::ostream_iterator<char>(cout));
    cout << endl;

    step_iterator<char*> first(s), last(s + 8);
    std::copy(first, last,
            std::ostream_iterator<char>(cout));

}

///////////////////////////////////////

int main()
{
    std::cout << "hello iterator_facade" << std::endl;

    case1();
    case2();
}
