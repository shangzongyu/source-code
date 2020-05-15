// Copyright (c) 2016
// Author: Chrono Law
#include <boost/preprocessor.hpp>

// gcc -P -E -o a.out basic.cpp;cat a.out;rm a.out

/////////////////

#if 0x10 > -1L
#               // do nothing
#endif

// no float in if
//#if 3.14 > 0
//#
//#endif

/////////////////

#define t1 3.14
#define t2 ~!@#$%^&*()-+
#define t3 'snake'
#define t4 "quiet"

// check meta data
t1
t2
t3
t4

/////////////////

#define data1   vector
#define data2   boost::factory

// check meta data
data1
data2

/////////////////

#define func(x,y)   int x = y
#define vfunc(x,...) x{__VA_ARGS__}

// call meta function
func(data1, data2)
vfunc(vector v, 1,2,3)

/////////////////

#define op1(x)  BOOST_PP_STRINGIZE(x)
#define op2(x,y,z)  BOOST_PP_CAT(x, \
                    BOOST_PP_CAT(y,z))
//#define op1(x)  #x
//#define op2(x,y,z)  x##y##z

op1(data1)
op2(data1, data2, z)

/////////////////
#undef data1
#undef data2
