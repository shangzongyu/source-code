#!/usr/bin/python3
# monddyyyy_to_iso.py: Convert dates from mon[.] dd, yyyy to ISO format.

# Assumes tab-delimited, linefeed-terminated input

import re
import sys
import fileinput
import warnings

map = {"jan": 1, "feb": 2, "mar": 3, "apr": 4, "may": 5, "jun": 6,
       "jul": 7, "aug": 8, "sep": 9, "oct": 10, "nov": 11, "dec": 12
      } # map 3-char month abbreviations to numeric month

for line in fileinput.input(sys.argv[1:]):
  values = line.rstrip().split("\t", 10000)    # split, preserving all fields
  for i in range(0, len(values)):
    # reformat the value if it matches the pattern, otherwise assume
    # that it's not a date in the required format and leave it alone
    m = re.match('^([^.]+)\.? (\d+), (\d+)$', values[i])
    if m:
      # use lowercase month name
      (month, day, year) = (m.group(1).lower(), int(m.group(2)), int(m.group(3)))
#@ _CHECK_VALIDITY_
      if month in map:
#@ _CHECK_VALIDITY_
        values[i] = "%04d-%02d-%02d" % (year, map[month], day)
      else:
        # warn, but don't reformat
        warnings.warn("%s bad date?" % (values[i]))
  print("\t".join(values))
