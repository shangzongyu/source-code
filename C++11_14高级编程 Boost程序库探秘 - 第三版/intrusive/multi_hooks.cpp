// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/operators.hpp>
#include <boost/next_prior.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/assign/ptr_list_of.hpp>

#include <boost/intrusive/list.hpp>
#include <boost/intrusive/set.hpp>
#include <boost/intrusive/unordered_set.hpp>
using namespace boost::intrusive;
using namespace boost;

///////////////////////////////////////

class point: 
    public list_base_hook<>,
    public unordered_set_base_hook<tag<struct us_tag>>
{
public:
    int x,y;
    point(int a = 0, int b = 0):
        x(a), y(b){}

    set_member_hook<> m_shook;
    set_member_hook<> m_mshook;

    friend bool operator==(const point& l, const point& r)
    {   return l.x == r.x && l.y == r.y;}

    friend bool operator<(const point& l, const point& r)
    {   return l.x < r.x;   }

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
        ptr_list_of<point>(0)(1)(2)(3)(4)(3)(2);

    typedef make_list<point>::type list_t; 

    typedef make_unordered_set<point,
        base_hook<unordered_set_base_hook<tag<us_tag>>> >::type uset_t;

    typedef make_set<point,
        member_hook<point, set_member_hook<>, &point::m_shook>>::type set_t;

    typedef make_multiset<point,
        member_hook<point, set_member_hook<>, &point::m_mshook>>::type mset_t;

    list_t lt(vec.rbegin(), vec.rend());
    for(auto& p : lt)
    {
        cout << p.x << ",";
    }
    cout << endl;

    set_t s(lt.begin(), lt.end());
    mset_t ms(lt.begin(), lt.end());
    assert(s.size() == 5 && ms.size() == 7);

    uset_t::bucket_type buckets[20];
    uset_t us(uset_t::bucket_traits(buckets, 20));

    us.insert(vec.begin(), vec.end());
    assert(us.size() == 5);

    lt.pop_front();
    assert(lt.size() == 6 &&
        s.size() == 5 && ms.size() == 7);

    set_t::iterator iter = 
        set_t::s_iterator_to(*us.begin());
    cout << iter->x << endl;

}

///////////////////////////////////////

int main()
{
    std::cout << "hello intrusive multi hooks" << std::endl;

    case1();
}
