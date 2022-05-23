#!/usr/bin/python3
# isoize_date.py: Read input data, look for values that match
# a date pattern, convert them to ISO format. Also converts
# 2-digit years to 4-digit years, using a transition point of 70.
# By default, this looks for dates in MM-DD-[CC]YY format.
# Does not check whether dates actually are valid (for example,
# won't complain about 13-49-1928).

# Assumes tab-delimited, linefeed-terminated input lines.

import sys
import re
import fileinput

# transition point at which 2-digit XX year values are assumed to be
# 19XX (below that, they are treated as 20XX)
transition = 70

for line in fileinput.input(sys.argv[1:]):
  val = line.split("\t", 10000);  # split, preserving all fields
  for i in range(0, len(val)):
    # look for strings in MM-DD-[CC]YY format
    m = re.match('^(\d{1,2})\D(\d{1,2})\D(\d{2,4})$', val[i])
    if not m:
      continue

    (month, day, year) = (int(m.group(1)), int(m.group(2)), int(m.group(3)))
    # to interpret dates as DD-MM-[CC]YY instead, replace preceding
    # line with the following one:
    # (day, month, year) = (int(m.group(1)), int(m.group(2)), int(m.group(3)))

    # convert 2-digit years to 4 digits, then update value in array
    if year < 100:
      year += 1900 if year >= transition else 2000
    val[i] = "%04d-%02d-%02d" % (year, month, day)
  print("\t".join (val))
