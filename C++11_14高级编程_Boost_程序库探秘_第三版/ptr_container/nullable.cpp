// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/noncopyable.hpp>

#include <boost/ptr_container/ptr_vector.hpp>
using namespace boost;

///////////////////////////////////////

void case1()
{
    typedef ptr_vector<nullable<int> > ptr_null_vec;
    ptr_null_vec vec;

    vec.push_back(nullptr);
    vec.push_back(new int(100));

    assert(vec.is_null(0));
    assert(!vec.is_null(1));

    for (auto i = vec.begin();
            i != vec.end(); ++i)
    {
        if (!boost::is_null(i))
        {   cout << *i << " ";  }
    }

    cout << endl;
}

///////////////////////////////////////

class item : boost::noncopyable
{
public:
    virtual ~item(){}
    virtual void print() = 0;
};
class abstract_item : public item
{
    string name;
public:
    abstract_item(const string& str):name(str){}
    virtual ~abstract_item(){}

    virtual void print() final override
    {   cout << name << endl; }
};

class television : public abstract_item
{
public:
    television():abstract_item("television")
    {}
};
class computer : public abstract_item
{
public:
    computer():abstract_item("computer")
    {}
};
class null_item final : public item
{
    virtual void print() {}
};

void case2()
{
    typedef ptr_vector<item> ptr_vec;
    ptr_vec vec;

    vec.push_back(new television);
    vec.push_back(new computer);
    vec.push_back(new null_item);

    for(auto& i : vec)
    {
        i.print();
    }

    vec.replace(2, new computer);
    vec[2].print();
}

///////////////////////////////////////
#include <boost/assign/ptr_list_inserter.hpp>

void case3()
{
    typedef ptr_vector<item> ptr_vec;
    ptr_vec vec;

    using namespace boost::assign;

    ptr_push_back<television>(vec)();
    ptr_push_back<computer>(vec)();

    ptr_vec v2;
    v2.transfer(v2.begin(), vec.begin(), vec);

    {
        //ptr_vec v2(vec);
        //v2 = vec.clone();
    }

}


///////////////////////////////////////

int main()
{
    std::cout << "hello nullable" << std::endl;

    case1();
    case2();
    case3();
}
