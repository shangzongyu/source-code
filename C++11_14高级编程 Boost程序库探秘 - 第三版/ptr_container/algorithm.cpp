// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/next_prior.hpp>
#include <boost/assign/ptr_list_inserter.hpp>
#include <boost/assign/ptr_map_inserter.hpp>

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_deque.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/ptr_container/ptr_set.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/ptr_container/ptr_unordered_set.hpp>
#include <boost/ptr_container/ptr_unordered_map.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    using namespace boost::assign;

    ptr_deque<int> dq;
    ptr_push_back(dq)(1)(2)(10)(10)(9);

    cout << std::count(dq.begin(), dq.end(), 10);
    cout << endl;

    cout << std::count_if(dq.begin(), dq.end(), 
            [](int x){ return x > 8;});
            //boost::bind(std::greater<int>(), _1, 8));
    cout << endl;

    cout << *std::min_element(dq.begin(), dq.end());
    cout << endl;
    cout << *std::max_element(dq.begin(), dq.end());
    cout << endl;

    cout << *std::find(dq.begin(), dq.end(), 2);
    cout << endl;

    cout << std::accumulate(dq.begin(), dq.end(), 0);
    cout << endl;

    ptr_list<int> lt(dq.begin(), dq.end());

    assert(std::equal(dq.begin(), dq.end(), lt.begin()));

    cout << endl;
}

///////////////////////////////////////
#include <boost/ptr_container/ptr_inserter.hpp>

void case2()
{
    using namespace boost::assign;

    ptr_deque<int> dq;
    ptr_push_back(dq)(1)(2)(10)(10)(9);

    std::transform(dq.begin(), dq.end(), dq.begin(),
            [](int x){ return x+3;});
            //boost::bind(std::plus<int>(), _1, 3));
    assert(dq.front() == 4);

    std::replace(dq.begin(), dq.end(), 13, 20);
    assert(dq[2] == 20);

    std::fill(dq.begin(), dq.end(), 99);
    assert(dq.back() == 99);

    ptr_vector<int> vec;
    ptr_push_back(vec)(1)(2)(3);

    std::copy(dq.begin(), boost::next(dq.begin(), 3),
            vec.begin());
    assert(vec[1] == 99);

    {
        ptr_vector<int> vec(10);
        //std::copy(dq.begin(), dq.end(), vec.begin());   // exception!

        std::copy(dq.begin(),dq.end(),
                ptr_container::ptr_back_inserter(vec));
    }

}

///////////////////////////////////////

void case3()
{
    using namespace boost::assign;

    ptr_deque<int> dq;
    ptr_push_back(dq)(20)(1)(2)(10)(9)(10)(100);

    std::reverse(dq.begin(), dq.end());
    for(auto& x : dq)
    {
        cout << x << ",";
    }
    cout << endl;

    std::stable_sort(dq.begin(), dq.end());
    for(auto& x : dq)
    {
        cout << x << ",";
    }
    cout << endl;

    dq.erase(std::unique(dq.begin(), dq.end()), dq.end());

    dq.erase(std::remove(dq.begin(), dq.end(), 20), dq.end());

    std::random_shuffle(dq.begin(), dq.end());

    std::partial_sort(dq.begin(), boost::next(dq.begin(), 3), dq.end());

    for(auto& x : dq)
    {
        cout << x << ",";
    }
    cout << endl;
}

///////////////////////////////////////

void case4()
{
    using namespace boost::assign;

    ptr_deque<int> dq;
    ptr_push_back(dq)(1)(2)(9)(10)(20);

    assert(std::binary_search(dq.begin(), dq.end(), 9));
    cout << *std::lower_bound(dq.begin(), dq.end(), 3);
    cout << endl;
    cout << *std::upper_bound(dq.begin(), dq.end(), 10);
    cout << endl;

    ptr_vector<int> vec;
    ptr_push_back(vec) (2)(9)(10);
    assert(std::includes(dq.begin(), dq.end(),
                vec.begin(), vec.end()));

}

///////////////////////////////////////

void case5()
{
    using namespace boost::assign;

    ptr_deque<int> dq;
    ptr_push_back(dq)(1)(2)(9)(10)(20);

    ptr_vector<int> vec;
    ptr_push_back(vec)(1)(2)(3);

    ptr_list<int> lt;

    std::set_union(dq.begin(), dq.end(),
            vec.begin(), vec.end(), 
            ptr_container::ptr_back_inserter(lt));

    for(auto& x : lt)
    {
        cout << x << ",";
    }
    cout << endl;

    lt.clear();

    std::set_intersection(dq.begin(), dq.end(),
            vec.begin(), vec.end(), 
            ptr_container::ptr_back_inserter(lt));

    for(auto& x : lt)
    {
        cout << x << ",";
    }
    cout << endl;
}

///////////////////////////////////////

void case6()
{
    using namespace boost::assign;

    ptr_deque<int> dq;
    ptr_push_back(dq)(100)(1)(2)(10)(9);

    dq.sort(dq.begin(), boost::next(dq.begin(), 3));

    ptr_list<int> lt(dq.begin(), dq.end());

    lt.sort(std::greater<int>());

    ptr_vector<int> vec;
    ptr_push_back(vec)(100)(1)(2)(2)(2)(10)(9)(7)(9);

    vec.unique();

}

///////////////////////////////////////

void case7()
{
    using namespace boost::assign;

    ptr_vector<int> vec;
    ptr_push_back<int>(vec)(100)(1)(2)(2)(2)(10)(9)(7)(9);

    vec.erase_if([](int x){ return x==2;});
    //vec.erase_if(boost::bind(std::equal_to<int>(), _1, 2));
    for(auto& x : vec)
    {
        cout << x << ",";
    }
    cout << endl;

    vec.erase_if(vec.begin(), boost::next(vec.begin(), 4),
            [](int x){ return x > 1;});
            //boost::bind(std::greater<int>(), _1, 1));
    for(auto& x : vec)
    {
        cout << x << ",";
    }
    cout << endl;

}

///////////////////////////////////////

void case8()
{
    using namespace boost::assign;

    ptr_vector<int> vec;
    ptr_push_back<int>(vec)(1)(2)(7)(9)(10);

    ptr_vector<int> v2;
    ptr_push_back(v2)(3)(5)(100);

    v2.merge(vec);
    assert(vec.empty());

}

///////////////////////////////////////

void case9()
{
    using namespace boost::assign;

    ptr_unordered_set<int> us;
    ptr_insert(us)(3)(5)(7)(13);

    assert(us.find(5) != us.end());
    assert(us.find(10) == us.end());
    assert(us.count(10) == 0);

    ptr_multimap<int, int> mm;
    ptr_map_insert(mm)(1, 1)(1, 5)(2, 2)(3, 4);

    assert(mm.count(1) == 2);
    assert(*mm.find(3)->second == 4);

}

///////////////////////////////////////

void case10()
{
    using namespace boost::assign;

    ptr_multiset<int> us;
    ptr_insert(us)(3)(5)(7)(13)(3);

    assert(us.count(3) ==2);

    auto r1 = us.equal_range(3);
    assert(!r1.empty() );
    assert(r1.front() == 3);

    ptr_unordered_multimap<int, int> mm;
    ptr_map_insert(mm)(1, 1)(1, 5)(2, 2)(3, 4);

    auto r2 = mm.equal_range(1);
    for (auto p = r2.begin(); p != r2.end(); ++p)
    {
        cout << *p->second << ",";
    }
    cout << endl;

}

///////////////////////////////////////

void case11()
{
    using namespace boost::assign;

    ptr_set<int> us;
    ptr_insert(us)(3)(5)(13)(7)(2);

    assert(*us.lower_bound(4) == 5);
    assert(*us.upper_bound(4) == 5);
    assert(*us.upper_bound(5) == 7);

}

///////////////////////////////////////

int main()
{
    std::cout << "hello ptr algorithm" << std::endl;

    case1();
    case2();
    case3();
    case4();
    case5();
    case6();
    case7();
    case9();
    case10();
    case11();
}

