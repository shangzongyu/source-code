#!/usr/bin/python3
# cvt_date.py: Read input data, look for values that match a date
# format, convert them to another format. Also converts 2-digit
# years to 4-digit years on request. By default, assumes a
# transition point of 70, but this can be changed.

# Assumes tab-delimited, linefeed-terminated input lines.

# To add another format:
# - Modify argument processing code
# - Add a case to the input value test
# - Add a case to the output date formatting test

# Shortcoming: Doesn't accommodate trailing times (for date/time values)

import sys
import re
import getopt
import fileinput
import warnings

def check_date_format(format, type):
  if re.match('^iso', format, re.IGNORECASE):
    return "iso"
  if re.match('^us', format, re.IGNORECASE):
    return "us"
  if re.match('^br', format, re.IGNORECASE):
    return "british"
  sys.exit("Invalid %s date format: %s" % (type, format))

# Determine whether a year is a leap year.  Requires 4-digit
# year value (e.g., "1993", not "93").

def is_leap_year(year):
  return ((year % 4 == 0) and ((year % 100 != 0) or (year % 400 == 0) ) )

# Given year and month, return the number of days in the month.  Year
# value must be in 4-digit form or the leap-year test won't be correct.

def days_in_month(year, month):
  day_tbl = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31] 
  days = day_tbl[month - 1]

  if month == 2 and is_leap_year(year):
    days += 1
  return days

# Given an array of integers representing year, month, and day of a date,
# determine whether the date is valid.

def is_valid_date(year, month, day):
  # year must be nonnegative, month and day must be positive
  if year < 0 or month < 0 or day < 1:
    return 0
  # check maximum limits on individual parts
  if year > 9999 or month > 12 or day > days_in_month(year, month):
    return 0
  return 1

prog = "cvt_date.py"
usage = f'''
Usage: {prog} [ options ] [ data_file ]

Options:
--help
    Print this message
--iformat=format_name, --if=format_name
    Set date format for input (iso, us, british; default is iso)
--oformat=format_name, --of=format_name
    Set date format for output (iso, us, british; default is iso)
--warn
    Warn about bad dates
--add-century
    Convert 2-digit years to 4 digits
--transition
    Within-century transition point for 2-digit to 4-digit conversion
    (implies --add-century); default is 70
--columns=column_list
    Convert only specific columns; column_list is a comma-separated list
    of column numbers (first column is numbered 1)

Other arguments:
data_file
    Name of data file to convert
'''

iformat = "iso"
oformat = "iso"
transition = 70
warn = False
add_century = False
filter_columns = False
columns = {}
yearfmt = "%02d"

long_options = ["help", "if=", "iformat=", "of=", "oformat=", "warn", "add-century", "transition="]

try:
  opts, args = getopt.getopt(sys.argv[1:], '', long_options)
except getopt.GetoptError as err:
  print(usage)
  sys.exit(2)

for o, a in opts:
  if o == "--help":
    print(usage)
    sys.exit(0)
  if o in("--if", "--iformat"):
    iformat = check_date_format(a, "input")
  if o in("--of", "--oformat"):
    oformat = check_date_format(a, "output")
  if o == "--warn":
    warn = True
  if o == "--add-century":
    add_century = True
    yearfmt = "%04d"
  if o == "--transition":
    transition = a
  if o == "--columns":
    cols = a.split(",")
    for c in cols:
      if re.match('^\d+$', c):
        if int(c) <= 0:
          sys.exit("Column specifier %s is not a positive integer" % (c))
        columns[int(c)] = 1
      else:
        m = re.match('^(\d+)-(\d+)$', c)
        if not m:
          sys.exit("%s is not a valid column specifier" % (c))
        (begin, end) = (int(m.group(1)), int(m.group(2)))
        if begin < 0 or end < 0 or begin > end:
          sys.exit("%s is not a valid column specifier" % (c))
        while begin <= end:
          columns[begin] = 1
          begin += 1
    filter_columns = True

# 2-digit years don't provide accurate leap year testing
if warn and not add_century:
  warnings.warn("NOTE: --warn without --add-century may produce spurious warnings")

line_num = 0
for line in fileinput.input(args):
  line_num += 1
  values = line.rstrip().split("\t", 10000)  # split, preserving all fields
  for i in range(0, len(values)):
    # don't process the value if a column list was
    # specified but this column isn't one of them
    if filter_columns and i not in columns:
      continue

    val = values[i]
    if iformat == "iso":
      m = re.match('^(\d{2}|\d{4})\D(\d{1,2})\D(\d{1,2})$', val)
      if m:
        (y, m, d) = (int(m.group(1)), int(m.group(2)), int(m.group(3)))
      else:
        continue
    elif iformat == "us":
      m = re.match('^(\d{1,2})\D(\d{1,2})\D(\d{2}|\d{4})$', val)
      if m:
        (m, d, y) = (int(m.group(1)), int(m.group(2)), int(m.group(3)))
      else:
        continue
    elif iformat == "british":
       m = re.match('^(\d{1,2})\D(\d{1,2})\D(\d{2}|\d{4})$', val)
       if m:
         (d, m, y) = (int(m.group(1)), int(m.group(2)), int(m.group(3)))
       else:
         continue
    else:  # not a recognizable date; go to next value
      continue

    # convert 2-digit year to 4 digits on request
    if add_century and y < 100:
      y += 1900 if y >= transition else 2000

    if warn and not is_valid_date(y, m, d):
      warnings.warn("line %d: %s invalid?" % (line_num, val))

    if oformat == "iso":
      val = f"{yearfmt}-%02d-%02d" % (y, m, d)
    elif oformat == "us":
      val = f"%02d-%02d-{yearfmt}" % (m, d, y)
    elif oformat == "british":
      val = f"%02d-%02d-{yearfmt}" % (d, m, y)
    else:
      # should never happen!
      sys.exit("Logic error: unknown output format %s" % (oformat));
    values[i] = val  # replace original value with new one
  print ("\t".join(values))
