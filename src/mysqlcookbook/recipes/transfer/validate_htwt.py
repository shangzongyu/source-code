#!/usr/bin/python3
# validate_htwt.py: Height/weight validation example.

# Assumes tab-delimited, linefeed-terminated input lines.

# Input columns and the actions to perform on them are as follows:
# 1: name; echo as given
# 2: birth; echo as given
# 3: height; validate as positive integer
# 4: weight; validate as positive integer

import sys
import fileinput
import warnings
from cookbook_utils import *

line_num = 0
for line in fileinput.input(sys.argv[1:]):
  line_num += 1
  (name, birth, height, weight) = line.rstrip().split ("\t", 4)
  if not is_positive_integer(height):
    warnings.warn(f"line {line_num}:height {height} is not a positive integer")
  if not is_positive_integer(weight):
    warnings.warn(f"line {line_num}:weight {weight} is not a positive integer")

