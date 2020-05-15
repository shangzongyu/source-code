// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/core/ignore_unused.hpp>
#include <boost/compressed_pair.hpp>
using namespace boost;

class empty1{};

class empty2
{
    static const int MAX = 100;
};

class empty3
{
public:
    void print()
    {   std::cout << "this is a empty class." << std::endl;}
};

///////////////////////////////////////

void case1()
{
    assert(sizeof(empty1) == 1);
    assert(sizeof(std::greater<int>) == 1);

    typedef compressed_pair<int, string> pair_type;

    pair_type cp1;

    pair_type cp2(10);

    pair_type cp3("hello");

    pair_type cp4(20, "pair");

    pair_type cp5(cp2);
    cp1 = cp4;

}

///////////////////////////////////////

void case2()
{
    int i = 313;
    string s;

    compressed_pair<int&, string&> cp(i, s);
    std::pair<int&, string&> p(i, s);

}

///////////////////////////////////////

void case3()
{
    compressed_pair<int, string> cp;
    assert(cp.second().empty());

    cp.first() = 10;
    cp.second() = "hello";

    assert(10 == cp.first());
    assert(!cp.second().empty());

    assert(sizeof(compressed_pair<int, empty1>) == sizeof(int));
    assert(sizeof(std::pair<int, empty1>) > sizeof(int));
    cout << sizeof(std::pair<int, empty1>)  << endl;

    cout << sizeof(compressed_pair<empty1, empty2>) << endl;
    cout << sizeof(std::pair<empty1, empty2>) << endl;

}

///////////////////////////////////////

template<typename T1, typename T2> inline
compressed_pair<T1, T2>
make_compressed_pair(T1 t1, T2 t2)
{
    return compressed_pair<T1, T2>(t1, t2);
}

template<typename P, int Version>
struct _compare
{
    bool operator()(const P& l, const P& r)
    {  return false;}
};

template<typename P>
struct _compare<P,0>
{
    bool operator()(const P& l, const P& r)
    {  return l.first() == r.first() && l.second() == r.second() ; }
};

template<typename P>
struct _compare<P,1>
{
    bool operator()(const P& l, const P& r)
    {  return l.second() == r.second() ; }
};

template<typename P>
struct _compare<P,2>
{
    bool operator()(const P& l, const P& r)
    {  return l.first() == r.first() ; }
};

template<typename P>
struct _compare<P,3>
{
    bool operator()(const P& l, const P& r)
    {  return true ; }
};

template<typename P>
struct _compare<P,4>
{
    bool operator()(const P& l, const P& r)
    {  return true ; }
};

template<typename P>
struct _compare<P,5>
{
    bool operator()(const P& l, const P& r)
    {  return l.first() == r.first() && l.second() == r.second() ; }
};

template<typename T1, typename T2>
bool operator==(const compressed_pair<T1, T2>& l, const compressed_pair<T1, T2>& r)
{
    typedef compressed_pair<T1, T2> pair_type;
    typedef
      boost::details::compressed_pair_switch
        <T1, T2,
        boost::is_same<
            typename boost::remove_cv<T1>::type,
            typename boost::remove_cv<T2>::type
            >::value,
        boost::is_empty<T1>::value,
        boost::is_empty<T2>::value
      > version;

  return _compare<pair_type, version::value>()(l,r);
}

template<typename T1, typename T2>
bool operator!=(const compressed_pair<T1, T2>& l, const compressed_pair<T1, T2>& r)
{
    return !(l==r);
}

void case4()
{
    {
        auto cp1 = make_compressed_pair(10, "char*");
        auto cp2 = make_compressed_pair(3.14, empty1());

        boost::ignore_unused(cp1, cp2);
    }

    compressed_pair<int, double> cp1(10,0), cp2(10,0);
    assert (cp1 == cp2);

    compressed_pair<int, empty1> cp3(0), cp4(10);
    assert(cp3 != cp4);

    compressed_pair<empty1, empty2> cp5, cp6;
    assert (cp5 == cp6);

    compressed_pair<empty1, empty1> cp7, cp8;
    assert (cp7 == cp8);

    compressed_pair<int, int> cp9(9,1), cp10(10,2);
    assert (cp9 != cp10);

}

///////////////////////////////////////

int main()
{
    std::cout << "hello compressed_pair" << std::endl;

    case1();
    case2();
    case3();
    case4();
}
