// Copyright (c) 2016
// Author: Chrono Law
#include <std.hpp>
using namespace std;

#include <boost/function_types/property_tags.hpp>
#include <boost/function_types/is_function.hpp>
#include <boost/function_types/is_function_pointer.hpp>
#include <boost/function_types/is_function_reference.hpp>
#include <boost/function_types/is_member_function_pointer.hpp>
#include <boost/function_types/is_member_object_pointer.hpp>
#include <boost/function_types/is_member_pointer.hpp>
#include <boost/function_types/is_callable_builtin.hpp> 
#include <boost/function_types/is_nonmember_callable_builtin.hpp>

using namespace boost;

namespace ft = boost::function_types;
using namespace ft;

typedef int (Func0)(...);
typedef void(Func1)(int);
typedef int (Func2)() volatile;

typedef Func0& RFunc0;
typedef Func1* PFunc1;
typedef bool (string::*Func3)()const;

///////////////////////////////////////

void case1()
{
    assert((ft::is_function<Func0, variadic>::value));
    assert((ft::is_function<Func0, default_cc>::value));
    assert((ft::is_function<Func1, non_cv>::value));
    assert((!ft::is_function<Func2, const_qualified>::value));
    assert((!ft::is_function<Func2, volatile_qualified>::value));

    assert((ft::is_function_reference<RFunc0, variadic>::value));
    assert((ft::is_function_pointer<PFunc1, non_cv>::value));
    assert((ft::is_member_pointer<Func3, const_qualified>::value));
    assert((ft::is_member_function_pointer<Func3>::value));
    assert((ft::is_callable_builtin<PFunc1>::value));
    assert((ft::is_nonmember_callable_builtin<RFunc0>::value));


}

///////////////////////////////////////
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/components.hpp>

#include <boost/mpl/front.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/size.hpp>


void case2()
{
    using namespace ft;

    assert((std::is_same<result_type<Func1>::type, void>::value)) ;
    assert(function_arity<Func1>::value == 1);

    typedef ft::parameter_types<Func1> Fp1;
    assert((mpl::size<Fp1>::value == 1));   
    assert((std::is_same<typename mpl::front<Fp1>::type, int>::value));

    typedef bool (string::*Func4)(const char *, size_t);
    typedef ft::parameter_types<Func4> Fp4;
    assert((mpl::size<Fp4>::value == 3));
    assert((std::is_same<typename mpl::front<Fp4>::type, string&>::value));
    assert((std::is_same<typename mpl::back<Fp4>::type, size_t>::value));

    typedef ft::components<Func1>   C1;
    assert((mpl::size<C1>::value == 2));
    assert((std::is_same<typename mpl::front<C1>::type,
                result_type<Func1>::type>::value));

}

///////////////////////////////////////
#include <boost/function_types/function_type.hpp>
#include <boost/function_types/function_pointer.hpp>
#include <boost/function_types/function_reference.hpp>
#include <boost/function_types/member_function_pointer.hpp>

#include <boost/mpl/vector.hpp>

void case3()
{
    typedef mpl::vector<void, int> types1;

    typedef ft::function_type<types1>::type Ft1;
    assert((std::is_same<Func1, Ft1>::value));

    typedef ft::function_pointer<types1>::type Ftp1;
    assert((std::is_same<PFunc1, Ftp1>::value));

    typedef ft::member_function_pointer<
        typename mpl::vector<bool, string&>::type,
                 const_qualified
                     >::type Ftp3;
    assert((std::is_same<Func3, Ftp3>::value));

}

///////////////////////////////////////

int main()
{
    std::cout << "hello function_types" << std::endl;

    case1();
    case2();
    case3();
}

