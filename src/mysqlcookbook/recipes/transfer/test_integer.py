#!/usr/bin/python3
# test_integer.py: Exercise the integer-testing library functions.

import cookbook_utils as cu

values = [
  "",
  "x",
  "-1",
  "0",
  "+1",
  "1",
  "-1.1",
  "+1.1",
  "1.1",
  ".1",
]

print("value  integer  unsigned int  positive int");

for val in values:
  verdict = "yes" if cu.is_integer(val) else "no"
  u_verdict = "yes" if cu.is_unsigned_integer(val) else "no"
  p_verdict = "yes" if cu.is_positive_integer(val) else "no"
  print("%5s  %-7s  %-8s      %s" % (val, verdict, u_verdict, p_verdict))
