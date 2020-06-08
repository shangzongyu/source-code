// Copyright (c) 2016
// Author: Chrono Law
#include <boost/preprocessor.hpp>

// gcc -P -E -o a.out seq.cpp;cat a.out;rm a.out

/////////////////

#define seq1 (a)(b)(c)(d)(e)
#define seq2 (~123)([])(--{}--)

BOOST_PP_SEQ_SIZE(seq1)
BOOST_PP_SEQ_CAT(seq1)

int BOOST_PP_SEQ_HEAD(seq1);

#define helper(r, d, e) BOOST_PP_STRINGIZE(e)
BOOST_PP_SEQ_FOR_EACH(helper, ~, seq2)

#undef seq1
#undef seq2

/////////////////

#define bns_helper(r, d, e) namespace e {

#define begin_namespace(s)    \
    BOOST_PP_SEQ_FOR_EACH(bns_helper, ~, s)

#define ens_helper(r, d, e) }

#define end_namespace(s)    \
    BOOST_PP_SEQ_FOR_EACH(ens_helper, ~, s)

#define seq (boost) (detail) (test)

// namespace boost { namespace detail { namespace test {
begin_namespace(seq)

// } } }
end_namespace(seq)
