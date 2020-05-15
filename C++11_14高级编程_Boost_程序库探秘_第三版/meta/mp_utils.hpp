// Copyright (c) 2016
// Author: Chrono Law
#ifndef _MP_UTILS_HPP
#define _MP_UTILS_HPP

#define mp_arglist      template
#define mp_arg          typename
#define mp_function     struct
#define mp_data         typedef

#define mp_return(T)        mp_data T type
//#define mp_return(T)  using type=T
#define mp_exec(Func)   Func::type
#define mp_eval(Func)   Func::value

#endif  // _MP_UTILS_HPP
