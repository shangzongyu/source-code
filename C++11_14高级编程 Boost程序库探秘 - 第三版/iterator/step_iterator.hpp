// Copyright (c) 2016
// Author: Chrono Law
#ifndef STEP_ITERATOR_HPP_
#define STEP_ITERATOR_HPP_

#include <boost/iterator/iterator_facade.hpp>

template<typename I, std::ptrdiff_t N = 2>
class step_iterator:
    public boost::iterator_facade<
        step_iterator<I>,
        typename boost::iterator_value<I>::type const,
        boost::single_pass_traversal_tag>
{
private:
    I m_iter;
public:

    typedef boost::iterator_facade<
        step_iterator<I>,typename boost::iterator_value<I>::type const,
        boost::single_pass_traversal_tag> super_type;
    typedef step_iterator this_type;

    using typename super_type::reference;

public:
    step_iterator(I x):
        m_iter(x)   {}

    step_iterator(this_type const& other) = default;
    this_type& operator=(this_type const& other) = default;

    //step_iterator(this_type const& other):
    //    m_iter(other.m_iter){}

    //void operator = (this_type const& other)
    //{   m_iter = other.m_iter;  }
private:
    friend class boost::iterator_core_access;

    reference dereference() const
    {   return *m_iter; }

    void increment()
    {   std::advance(m_iter, N);    }

    bool equal(this_type const& other) const
    {   return m_iter == other.m_iter;}
};

#endif //STEP_ITERATOR_HPP_
