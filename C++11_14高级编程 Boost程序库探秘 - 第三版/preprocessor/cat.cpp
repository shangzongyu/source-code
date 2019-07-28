// Copyright (c) 2016
// Author: Chrono Law
#include <boost/preprocessor.hpp>

// gcc -P -E -o a.out cat.cpp;cat a.out;rm a.out

#define token BOOST_PP_CAT(x, y)

// check token == xy
token

