// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/next_prior.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/assign/ptr_list_of.hpp>

#include <boost/intrusive/list.hpp>
using namespace boost::intrusive;
using namespace boost;

///////////////////////////////////////

class point : public list_base_hook<>
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

    typedef make_list<point>::type list_t;
    //typedef make_list<point,
    //        member_hook<point,
    //        list_member_hook<>, &point::m_hook>>::type list_t;


    list_t lt;
    assert(lt.empty());

    lt.push_back(vec[2]);
    lt.push_front(vec[3]);

    assert(!lt.empty() && lt.size() == 2);
    assert(lt.front().x == 3);
    assert(lt.back().x == 2);

    lt.insert(boost::next(lt.begin()),
            vec.begin(), vec.begin() + 2);
    for(auto& p : lt)
    {
        cout << p.x << ",";
    }
    cout << endl;

    lt.reverse();
    lt.pop_front();
    assert(lt.size() == 3);

    lt.insert(boost::prior(lt.end()), vec[4]);

    lt.sort();

    lt.erase(boost::prior(lt.end(), 2));

    for(auto& p : lt)
    {
        cout << p.x << ",";
    }
    cout << endl;
}

///////////////////////////////////////

void case2()
{
    using namespace boost::assign;
    ptr_vector<point> vec =
        ptr_list_of<point>(0)(1)(2)(3)(4);

    typedef make_list<point>::type list_t;
    list_t lt(vec.begin(), vec.end());
    assert(lt.size() == 5);

    lt.shift_backwards(2);

    for(auto& p : lt)
    {
        cout << p.x << ",";
    }
    cout << endl;

    lt.shift_forward();

    for(auto& p : lt)
    {
        cout << p.x << ",";
    }
    cout << endl;

}

///////////////////////////////////////
#include <boost/checked_delete.hpp>
#include <boost/iterator/indirect_iterator.hpp>

struct disposer
{
    void operator()(point* p)
    {
        cout << "dispose:" << p->x << endl;
        checked_delete(p);
    }
};

void case3()
{
    std::vector<point*> vec;
    for (int i = 0;i < 5; ++i)
    {
        vec.push_back(new point(i, i));
    }

    typedef make_list<point>::type list_t;
    list_t lt(make_indirect_iterator(vec.begin()),
            make_indirect_iterator(vec.end()));

    disposer d;

    lt.pop_front_and_dispose(d);

    lt.erase_and_dispose(boost::next(lt.begin()), d);

    lt.remove_and_dispose(point(4, 4), d);
    lt.push_back(*(new point(3, 3)));

    lt.unique_and_dispose(d);

}

///////////////////////////////////////
#include <boost/functional/factory.hpp>

struct cloner
{
    template<typename T>
    T* operator()(const T& r)
    {   return factory<T*>()(r);}
};

void case4()
{
    using namespace boost::assign;
    ptr_vector<point> vec =
        ptr_list_of<point>(0)(1)(2)(3)(4);

    typedef make_list<point>::type list_t;
    list_t lt(vec.begin(), vec.end());

    list_t lt2;
    assert(lt2.empty());

    lt2.clone_from(lt, cloner(), disposer());
    assert(lt2 == lt);
}

///////////////////////////////////////

void case5()
{
    using namespace boost::assign;
    ptr_vector<point> vec =
        ptr_list_of<point>(0)(1)(2)(3)(4);

    typedef make_list<point>::type list_t;
    list_t lt;

    lt.push_back(vec[1]);
    lt.push_back(vec[3]);

    assert(vec[1].is_linked());
    assert(lt.iterator_to(vec[1]) == lt.begin());

    assert(vec[3].is_linked());
    assert(list_t::s_iterator_to(vec[3]) ==
            boost::prior(lt.end()));

    list_t& rlt = list_t::container_from_end_iterator(lt.end());
    assert(std::addressof(rlt) == std::addressof(lt));

}

///////////////////////////////////////

int main()
{
    std::cout << "hello intrusive list" << std::endl;

    case1();
    case2();
    case3();
    case4();
    case5();
}
