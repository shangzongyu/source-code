// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/operators.hpp>
#include <boost/next_prior.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/assign/ptr_list_of.hpp>

#include <boost/intrusive/set.hpp>
using namespace boost::intrusive;
using namespace boost;

///////////////////////////////////////

class point : public set_base_hook<>,
              boost::less_than_comparable<point>
{
public: 
    int x,y;
    point(int a = 0, int b = 0):
        x(a), y(b){}

    //list_member_hook<> m_hook;

    friend bool operator==(const point& l, const point& r)
    {   return l.x == r.x && l.y == r.y;}
    friend bool operator<(const point& l, const point& r)
    {   return l.x < r.x;   }

};

///////////////////////////////////////

void case1()
{
    using namespace boost::assign;
    ptr_vector<point> vec =
        ptr_list_of<point>(0)(1)(2)(3)(4);

    typedef make_set<point,
            compare<std::greater<point>> >::type set_t;
    set_t s;

    assert(s.empty());

    assert(s.insert(vec[0]).second);
    assert(s.insert(vec[2]).second);
    assert(!s.insert(vec[2]).second);

    assert(s.size() == 2);
    assert(s.count(point()) == 1);

    s.insert(vec.begin(), vec.end());
    assert(s.size() == 5);

    s.erase(s.lower_bound(2), s.upper_bound(2));

}

///////////////////////////////////////
#include <boost/iterator/indirect_iterator.hpp>
#include <boost/functional/factory.hpp>

struct disposer
{
    void operator()(point* p)
    {
        cout << "dispose:" << p->x << endl;
        checked_delete(p);
    }
};

struct cloner
{
    template<typename T>
    T* operator()(const T& r)
    {   return factory<T*>()(r);}
};

void case2()
{
    std::vector<point*> vec;
    for (int i = 0;i < 5; ++i)
    {
        vec.push_back(new point(i, i));
    }

    typedef make_set<point>::type set_t;
    set_t s(make_indirect_iterator(vec.begin()),
            make_indirect_iterator(vec.end()));

    s.erase_and_dispose(s.begin(), boost::next(s.begin(), 2),
            disposer());

    set_t s2;
    s2.clone_from(s, cloner(), disposer());
    assert(s2.begin()->x == 2);
    assert(s2 == s);

    assert(std::addressof(s2) ==
            std::addressof(s2.container_from_iterator(boost::next(s2.begin()))));

}

///////////////////////////////////////

struct key_compare
{
    typedef const int& key_type;
    typedef const point& value_type;

    bool operator()(key_type k, value_type p) const
    {   return k < p.x;}
    bool operator()(value_type p, key_type k) const
    {   return p.x < k;}
};

void case3()
{
    using namespace boost::assign;
    ptr_vector<point> vec =
        ptr_list_of<point>(0)(1)(2)(3)(4);

    typedef make_set<point>::type set_t;
    set_t s(vec.begin(), vec.end());

    key_compare kc;

    assert(s.count(1, kc) == 1);
    assert(s.find(2, kc)->x == 2);
    assert(s.find(9, kc) == s.end());

    assert(s.erase(3, key_compare()) == 1);
    assert(s.find(point(3)) == s.end());

}

///////////////////////////////////////

void case4()
{
    using namespace boost::assign;
    ptr_vector<point> vec =
        ptr_list_of<point>(0)(1)(2)(3)(4);

    typedef make_set<point>::type set_t;
    set_t s(vec.begin(),boost::next(vec.begin(), 3));

    set_t::insert_commit_data idata;

    assert(!s.insert_check(0, key_compare(), idata).second);

    assert(s.insert_check(4, key_compare(), idata).second);
    s.insert_commit(vec[4], idata);

    assert(s.find(4, key_compare()) != s.end());

}

///////////////////////////////////////

void case5()
{
    using namespace boost::assign;
    ptr_vector<point> vec =
        ptr_list_of<point>(0)(1)(2)(3)(4)(3)(2);

    typedef make_multiset<point>::type set_t;
    //typedef make_multiset<point,
    //        member_hook<point, set_member_hook<>, &point::m_hook>>::type set_t;

    set_t s(vec.begin(),vec.end());
    assert(s.size() == 7);

    s.erase(2, key_compare());
    assert(s.size() == 5);
    assert(s.count(2, key_compare()) == 0);
}


///////////////////////////////////////

int main()
{
    std::cout << "hello intrusive set" << std::endl;

    case1();
    case2();
    case3();
    case4();
    case5();
}
