// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/foreach.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/assign/ptr_list_of.hpp>

#include <boost/intrusive/unordered_set.hpp>
using namespace boost::intrusive;
using namespace boost;

///////////////////////////////////////

class point : public unordered_set_base_hook<>
{
public: 
    int x,y;
    point(int a = 0, int b = 0):
        x(a), y(b){}

    //list_member_hook<> m_hook;

    friend bool operator==(const point& l, const point& r)
    {   return l.x == r.x && l.y == r.y;}

    friend std::size_t hash_value(const point& p)
    {
        size_t seed = 2016;
        hash_combine(seed, p.x);
        hash_combine(seed, p.y);
        return seed;
    }

};

///////////////////////////////////////

void case1()
{
    using namespace boost::assign;
    ptr_vector<point> vec =
        ptr_list_of<point>(0)(1)(2)(3)(4);

    typedef make_unordered_set<point>::type set_t;

    std::vector<set_t::bucket_type> buckets(2);
    set_t s(vec.begin(), vec.end(),
        set_t::bucket_traits(&buckets[0], 2));

    assert(s.size() == 5);
    assert(s.count(point(1)) == 1);

    for(auto& p : s)
    {
        cout << p.x << ",";
    }
    cout << endl;

    s.erase(s.find(point(1)));
    assert(s.size() == 4);

    set_t::bucket_type buckets2[10];
    s.rehash(set_t::bucket_traits(buckets2, 10));

    s.clear();

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

    typedef make_unordered_set<point>::type set_t;

    std::vector<set_t::bucket_type> buckets(5);
    set_t s(make_indirect_iterator(vec.begin()),
            make_indirect_iterator(vec.end()),
            set_t::bucket_traits(&buckets[0], 5));

    s.erase_and_dispose(s.begin(), boost::next(s.begin(), 2),
            disposer());

    set_t::bucket_type buckets2[10];
    set_t s2(set_t::bucket_traits(buckets2, 10));

    s2.clone_from(s, cloner(), disposer());
    assert(*s2.begin() == *s.begin());

}

///////////////////////////////////////
typedef std::pair<int, int> ukey_type;
struct key_hasher
{
    std::size_t operator()(const ukey_type& k)
    {
        size_t seed = 2016;
        hash_combine(seed, k.first);
        hash_combine(seed, k.second);
        return seed;
    }
};
struct key_equal
{
    bool operator()(const ukey_type& k, const point& p)
    {
        return k.first == p.x && k.second == p.y;
    }
    bool operator()(const point& p, const ukey_type& k )
    {
        return operator()(k, p);
    }
};

void case3()
{
    using namespace boost::assign;
    ptr_vector<point> vec =
        ptr_list_of<point>(0)(1)(2)(3)(4);

    point tmp(5, 5);

    typedef make_unordered_set<point>::type set_t;

    std::vector<set_t::bucket_type> buckets(5);
    set_t s(vec.begin(), vec.end(),
            set_t::bucket_traits(&buckets[0], 2));

    key_hasher kh;
    key_equal  keq;

    assert(s.count(make_pair(1,0), kh, keq) == 1);
    assert(s.find(make_pair(2, 0), kh, keq) != s.end());

    s.erase(make_pair(4, 0), kh, keq);
    assert(s.find(make_pair(4, 0), kh, keq) == s.end());

    set_t::insert_commit_data idata;

    assert(s.insert_check(make_pair(5, 5), kh, keq, idata).second);
    s.insert_commit(tmp, idata);
    assert(s.find(make_pair(5, 5), kh, keq) != s.end());
}

///////////////////////////////////////

void case4()
{
    using namespace boost::assign;
    ptr_vector<point> vec =
        ptr_list_of<point>(0)(1)(2)(3)(4)(3)(2);

    typedef make_unordered_multiset<point>::type set_t;

    std::vector<set_t::bucket_type> buckets(5); 
    set_t s(set_t::bucket_traits(&buckets[0], 2));

    s.insert(vec.begin(), vec.end());
    assert(s.size() == vec.size());

    assert(s.count(point(2)) == 2);

    BOOST_FOREACH(point& p, 
        s.equal_range(make_pair(3, 0), key_hasher(), key_equal()))
    {
        cout << p.x << ",";
    }
}


///////////////////////////////////////

int main()
{
    std::cout << "hello intrusive unordered_set" << std::endl;

    case1();
    case2();
    case3();
}
