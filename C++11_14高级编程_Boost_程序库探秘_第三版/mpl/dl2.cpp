// Copyright (c) 2016
// Author: Chrono Law
#include <stdexcept>

#include <std.hpp>
using namespace std;

extern "C" {
#include <dlfcn.h>
}

#include <boost/utility/result_of.hpp>
#include <boost/type_traits.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/string.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/at.hpp>
namespace mpl = boost::mpl;

struct dl_front
{
    typedef mpl::string<'lib','test','.so'> so_name;

    typedef int (*Func1)(int);
    typedef int (*Func2)(int, int);

    typedef mpl::string<'so_','func','1'> fun1_name;
    typedef mpl::string<'so_','func','2'> fun2_name;

    typedef mpl::map<
        mpl::pair<fun1_name, Func1>,
        mpl::pair<fun2_name, Func2>
        >   map_fun;
};

template<typename Front>
class dl_back
{
private:
    void* m_h = nullptr;
public:
    dl_back()
    {
        m_h = dlopen(
                mpl::c_str<typename Front::so_name>::value, RTLD_NOW);
    }
    ~dl_back()
    {
        dlclose(m_h);
    }
public:
    //template<typename FuncName>
    //typename mpl::at<typename Front::map_fun, FuncName>::type
    //func()
    //{
    //    typedef typename
    //        mpl::at<typename Front::map_fun, FuncName>::type result_type;
    //            result_type pf = reinterpret_cast<result_type>
    //                (dlsym(m_h, mpl::c_str<FuncName>::value));

    //    return pf;
    //}

    template<typename FuncName>
    typename mpl::at<typename Front::map_fun, FuncName>::type
    func_ptr()
    {
        typedef typename
            mpl::at<typename Front::map_fun, FuncName>::type result_type;
                result_type pf = reinterpret_cast<result_type>
                    (dlsym(m_h, mpl::c_str<FuncName>::value));

        return pf;
    }
public:
    template<typename FuncName, typename ... Args >

    // result_of
    //typename boost::result_of<
    //    typename mpl::at<typename Front::map_fun, FuncName>::type(Args...)
    //    >::type

    // function_traits + remove_pointer
    typename boost::function_traits<
        typename boost::remove_pointer<
            typename mpl::at<typename Front::map_fun, FuncName>::type>::type
        >::result_type
    func(Args const& ... args)
    {
        //typedef typename mpl::at<typename Front::map_fun, FuncName>::type
        //    func_type;

        //func_type pf = reinterpret_cast<func_type>
        //    (dlsym(m_h, mpl::c_str<FuncName>::value));

        //return pf(args...);

        return func_ptr<FuncName>()(args...);
    }

};

int main()
{
    cout << "dll version 2" << endl;

    dl_back<dl_front> dl;

    cout << dl.func_ptr<dl_front::fun1_name>()(10) << endl;
    cout << dl.func_ptr<dl_front::fun2_name>()(10,20) << endl;

    cout << dl.func<dl_front::fun1_name>(10) << endl;
    cout << dl.func<dl_front::fun2_name>(10,20) << endl;
}
