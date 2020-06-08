// Copyright (c) 2016
// Author: Chrono Law
#include <boost/preprocessor.hpp>

// gcc -std=c++11 -P -E -o a.out functions.cpp;cat a.out;rm a.out

/////////////////

#if __cplusplus < 201103L
    BOOST_PP_ASSERT(0)
#endif

#define x BOOST_PP_MUL(6, 6)

BOOST_PP_ASSERT(BOOST_PP_EQUAL(x, 36))

#undef x

/////////////////

#define helper(z, n, d) BOOST_PP_CAT(d,n)
#define DECL_VARS(n, var) BOOST_PP_ENUM(n, helper, var)

int DECL_VARS(10, x);

#undef helper
#undef DECL_VARS

#define NGX_NULL_HELPER(z, n, d) d
#define NGX_MODULE_NULL(n)      \
    BOOST_PP_ENUM(n, NGX_NULL_HELPER, nullptr)

{NGX_MODULE_NULL(3)}

/////////////////

#define helper(z, n, d) d##n{n};
#define DECL_VARS(n, decl) BOOST_PP_REPEAT(n, helper, decl)

DECL_VARS(3, int x)

#undef helper
#undef DECL_VARS

