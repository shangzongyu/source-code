// Copyright (c) 2016
// Author: Chrono Law
#ifndef _PRO_BOOST_PERSON_HPP
#define _PRO_BOOST_PERSON_HPP

#include <boost/operators.hpp>
#include <boost/functional/hash.hpp>

class person:
    boost::less_than_comparable<person>
{
public:
    int         m_id;
    string  m_fname, m_lname;

    person(int id, const string& f, const string& l):
        m_id(id), m_fname(f), m_lname(l){}

    const string& first_name() const
    {   return m_fname;}

    string& last_name()
    {   return m_lname;}

    friend bool operator<(const person&l, const person& r)
    {   return l.m_id < r.m_id;}

    friend bool operator==(const person& l, const person& r)
    {   return l.m_id == r.m_id ;}

    friend std::size_t hash_value(const person& p)
    {
        size_t seed = 2016;
        boost::hash_combine(seed, p.m_fname);
        boost::hash_combine(seed, p.m_lname);
        return seed;
    }
};

struct person_name
{
    typedef string result_type;
    result_type operator()(const person& p) const
    {
        return p.m_fname + " "  +p.m_lname;
    }
    result_type operator()(person *const p) const
    {
        return p->m_fname + " "  +p->m_lname;
    }
};

string nameof(const person& p)
{
    return p.m_fname + " "  +p.m_lname;
}

#endif // _PRO_BOOST_PERSON_HPP
