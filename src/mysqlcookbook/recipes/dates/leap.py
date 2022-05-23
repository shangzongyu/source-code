#!/usr/bin/python
# leap.py: Leap-year test of ISO date strings

# set up an array of test dates

date_array = (
  "1899-01-01",
  "1900-01-01",
  "1999-01-01",
  "2000-01-01",
  "1963-01-01",
  "1964-01-01"
)

for date in date_array:
#@ _LEAP_TEST_
  year = int(date[0:4])
  is_leap = (year % 4 == 0) and (year % 100 != 0 or year % 400 == 0)
#@ _LEAP_TEST_
  print(date, year, is_leap)
