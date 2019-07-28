// Copyright (c) 2016
// Author: Chrono Law
#include <boost/preprocessor.hpp>

// gcc -P -E -o a.out arithmetic.cpp;cat a.out;rm a.out
#
#
#

#if 1+1 > 3
    #error test arithmetic in if/endif
#endif

#define calc(x, y) int x = y
//calc(x, 1+2)
calc(x, BOOST_PP_ADD(1,2))

#define x 1
#define y 2

#define v BOOST_PP_ADD(x, y)

// check v
v

#if v != 3
    BOOST_PP_ASSERT(0)
#endif

#define u BOOST_PP_SUB(v, x)
u

#if u != y
    BOOST_PP_ASSERT(0)
#endif

#define w BOOST_PP_INC(BOOST_PP_INC(u))
w

#if w != 4
    BOOST_PP_ASSERT_MSG(0)
#endif

#if BOOST_PP_BOOL(w)
#define a BOOST_PP_MOD(10, 4)
a
//#define b BOOST_PP_MUL(a, 300)
//b
#endif

