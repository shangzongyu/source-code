// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
#include <stack>
//using namespace std;

#include <boost/functional/hash.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    std::cout << std::hex;

    std::cout << hash<int>()(0x2000) << std::endl;
    std::cout << hash<double>()(1.732) << std::endl;
    std::cout << hash<const char*>()("string") << std::endl;

    std::complex<double> c(1.0, 2.0);
    std::cout << hash<decltype(c)>()(c) << std::endl;

    std::cout << hash<std::string>()("string") << std::endl;

    std::vector<int> v(12);
    std::cout << hash<decltype(v)>()(v) << std::endl;

    std::map<int, std::string> m;
    std::cout << hash<decltype(m)>()(m);

    std::array<int, 5> ar;
    std::cout << hash<decltype(ar)>()(ar) << std::endl;

    //std::stack<int> s;
    //std::cout << hash<decltype(s)>()(s) << std::endl;
}

///////////////////////////////////////

#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>

void case2()
{
    boost::unordered_set<int, boost::hash<int> > us;
    boost::unordered_map<int, std::string, boost::hash<int> > um;
}

///////////////////////////////////////

class person final
{
private:
    int id;
    std::string name;
    unsigned int age;
public:
    person(int a, const char* b, unsigned int c):
      id(a),name(b), age(c)
    {}

    size_t hash_value() const
    {
        //return hash<int>()(id);

        size_t seed = 1984;
        hash_combine(seed, id);
        hash_combine(seed, name);
        hash_combine(seed, age);

        return seed;
    }

    friend bool operator==(person const & l, person const & r)
    {   return l.id == r.id;}

};

size_t hash_value(person const & p)
{   return p.hash_value();}

void case3()
{
    person p(1, "adam", 20);
    std::cout << hash<person>()(p) << std::endl;

    unordered_set<person> us;                   //无序集合容器

    us.insert(person(1, "adam", 20));
    us.insert(person(2, "eva", 20));
    assert(us.size() == 2);

}

///////////////////////////////////////
class demo_class
{
private:
    std::vector<std::string> v;
    int x;
public:
    size_t hash_value()
    {
        size_t seed = 0;
        hash_combine(seed, x);
        hash_range(seed, v.rbegin(), v.rend());

        return seed;
    }
};

void case4()
{
    std::vector<int> v {1,2,5,8,15};
    auto hv = hash_range(v.begin(), v.end());

    unordered_set<int> us {1,2,5,8,15};
    hv = hash_range(us.begin(), us.end());

}

///////////////////////////////////////

int main()
{
    std::cout << "hello hash" << std::endl;

    case1();
    case2();
    case3();
    case4();
}
