// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/iterator/iterator_adaptor.hpp>
using namespace boost;

///////////////////////////////////////

template<typename P>
class array_iter:
    public boost::iterator_adaptor<array_iter<P>, P >
{
    BOOST_STATIC_ASSERT(std::is_pointer<P>::value);
public:
    typedef typename array_iter::iterator_adaptor_ super_type;
    array_iter(P x): super_type(x)
    {}
};

void case1()
{
    int a[10] = {1,2,3};
    array_iter<int*> start(a), finish(a + 10);
    start += 1;

    std::copy(start, finish,
            ostream_iterator<int>(cout, ","));

    cout << endl;
}

///////////////////////////////////////

template<typename I>
class delta_iterator : public boost::iterator_adaptor<
   delta_iterator<I>, I ,
   typename std::iterator_traits<I>::value_type,
   boost::single_pass_traversal_tag,
   typename std::iterator_traits<I>::value_type const >
{
private:
    friend class boost::iterator_core_access;
    typedef delta_iterator                       this_type;
    typedef typename this_type::iterator_adaptor_ super_type;

    typename super_type::value_type m_value;
public:
    explicit delta_iterator(const I& iter):
        super_type(iter),  m_value(0)
{}
private:
    using super_type::base;
    using super_type::base_reference;

    typename super_type::reference dereference() const
    {
        return m_value + *base();
    }

    void increment()
    {
        m_value += *base();
        ++base_reference();
    }
};

void case2()
{
    vector<int> a = {1,2,3};

    //typedef delta_iterator<vector<int>::const_iterator> delta_iter;
    typedef delta_iterator<decltype(a.cbegin())> delta_iter;

    delta_iter start(a.begin()), finish(a.end());

    std::copy(start, finish,
            ostream_iterator<int>(cout, ","));

}

///////////////////////////////////////

int main()
{
    std::cout << "hello iterator_adaptor" << std::endl;

    case1();
    case2();
}
