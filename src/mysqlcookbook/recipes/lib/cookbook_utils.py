# cookbook_utils.py: MySQL Cookbook utilities

import re

# Given database and table names, return a list containing the names
# of the table's columns, in table definition order.

#@ _GET_COLUMN_NAMES_
def get_column_names(conn, db_name, tbl_name):
  stmt = '''
         SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS
         WHERE TABLE_SCHEMA = %s AND TABLE_NAME = %s
         ORDER BY ORDINAL_POSITION
         '''
  cursor = conn.cursor()
  cursor.execute(stmt, (db_name, tbl_name))
  names = []
  for row in cursor:
    names.append(row[0])
  cursor.close()
  return names
#@ _GET_COLUMN_NAMES_

# Given database and table names, return information about the table
# columns. Return value is a dictionary keyed by column name. Each column
# name dictionary value is a dictionary keyed by name of column in the
# INFORMATION_SCHEMA.COLUMNS table.

#@ _GET_COLUMN_INFO_
def get_column_info(conn, db_name, tbl_name):
  stmt = '''
         SELECT * FROM INFORMATION_SCHEMA.COLUMNS
         WHERE TABLE_SCHEMA = %s AND TABLE_NAME = %s
         '''
  cursor = conn.cursor()
  cursor.execute(stmt, (db_name, tbl_name))
  # construct array of colum names (name of column in position i is
  # cursor.description[i][0]), and save the position at which 'COLUMN_NAME'
  # value appears
  col_names = []
  col_name_idx = -1
  for i, col_info in enumerate(cursor.description):
    col_name = col_info[0]
    col_names.append(col_name)
    if col_name == 'COLUMN_NAME':
      col_name_idx = i
  col_info = {}
  if col_name_idx < 0:
    print("get_column_info: Did not find COLUMN_NAME column")
    return {}
  else:
    # read info for each column, construct dictionary that maps each
    # INFORMATION_SCHEMA column name to its value, and associate this
    # dictionary with the column name in the col_info dictionary
    for row in cursor:
      col_info[row[col_name_idx]] = dict(zip(col_names, row))
  cursor.close()
  return col_info
#@ _GET_COLUMN_INFO_

# get_enumorset_info() - get metadata for an ENUM or SET column.
# Take a database connection and database, table, and column names.
# Return a dictionary keyed by "name", "type", "values", "nullable",
# and "default". Return None if no info available.

#@ _GET_ENUMORSET_INFO_
def get_enumorset_info(conn, db_name, tbl_name, col_name):
  cursor = conn.cursor()
  stmt = '''
         SELECT COLUMN_NAME, COLUMN_TYPE, IS_NULLABLE, COLUMN_DEFAULT
         FROM INFORMATION_SCHEMA.COLUMNS
         WHERE TABLE_SCHEMA = %s AND TABLE_NAME = %s AND COLUMN_NAME = %s
         '''
  cursor.execute(stmt, (db_name, tbl_name, col_name))
  row = cursor.fetchone()
  cursor.close()
  if row is None: # no such column
    return None

  # create dictionary to hold column information
  info = {'name': row[0]}
  # get data type string; make sure it begins with ENUM or SET
  s = row[1].decode()
  p = re.compile("(ENUM|SET)\((.*)\)$", re.IGNORECASE)
  match = p.match(s)
  if not match: # not ENUM or SET
    return None
  info['type'] = match.group(1)    # data type

  # get values by splitting list at commas, then applying a
  # quote-stripping function to each one
  s = match.group(2).split(',')
  f = lambda x: re.sub("^'(.*)'$", "\\1", x)
  info['values'] = map(f, s)

  # determine whether column can contain NULL values
  info['nullable'] = (row[2].upper() == 'YES')

  # get default value (None represents NULL)
  info['default'] = row[3]
  return info
#@ _GET_ENUMORSET_INFO_

# Check whether a value is a legal ENUM value.

#@ _CHECK_ENUM_VALUE_
def check_enum_value(conn, db_name, tbl_name, col_name, val):
  valid = 0
  info = get_enumorset_info(conn, db_name, tbl_name, col_name)
  if info is not None and info['type'].upper() == 'ENUM':
    # use case-insensitive comparison because default collation
    # (utf8mb4_0900_ai_ci) is case-insensitive (adjust if you use
    # a different collation)
    valid = 1 if list(map(lambda v: v.upper(), info['values'])).count(val.upper()) > 0 else 0
  return valid
#@ _CHECK_ENUM_VALUE_

# Check whether a value is a legal SET value; each element must be
# a legal element of the column.  (For example, 'blue,white' is a legal
# value for a set defined as 'red,white,blue'.)

# An empty string is always a legal set element.  No special test
# is required, because for the empty value, split returns an empty
# list and the loop never executes.

#@ _CHECK_SET_VALUE_
def check_set_value(conn, db_name, tbl_name, col_name, val):
  valid = 0
  info = get_enumorset_info(conn, db_name, tbl_name, col_name)
  if info is not None and info['type'].upper() == 'SET':
    if val == "":
      return 1 # empty string is legal element
    # use case-insensitive comparison because default collation
    # (utf8mb4_0900_ai_ci) is case-insensitive (adjust if you use
    # a different collation)
    valid = 1  # assume valid until we find out otherwise
    for v in val.split(','):
      if list(map(lambda x: x.upper(), info['values'])).count(v.upper()) <= 0:
        valid = 0
        break
  return valid
#@ _CHECK_SET_VALUE_


# Trim whitespace from the beginning and end of a string, returning
# the result.

#@ _TRIM_WHITESPACE_
def trim_whitespace(val):
  res = re.sub('^\s+', '', val)
  res = re.sub('\s+$', '', res)
  return res
#@ _TRIM_WHITESPACE_


# Return true if argument represents an integer (possible leading sign),
# an unsigned (nonnegative) integer, or a positive integer.

#@ _IS_INTEGER_
def is_integer(val):
  p = re.compile('^[-+]?\d+$')
  return p.match(val)
#@ _IS_INTEGER_

#@ _IS_UNSIGNED_INTEGER_
def is_unsigned_integer(val):
  p = re.compile('^\d+$')
  return p.match(val)
#@ _IS_UNSIGNED_INTEGER_

#@ _IS_POSITIVE_INTEGER_
def is_positive_integer(val):
  p = re.compile('^\+?\d+$')
  s = p.search(val)
  return s and (s.group(0) != '0')
#@ _IS_POSITIVE_INTEGER_


# Return true if argument represents a valid innings-pitched number
# (.1, 1, 1.2, etc.  Fractional digit, if present, must be 0, 1, or 2.)

#@ _IS_INNINGS_PITCHED_
def is_innings_pitched(val):
  pass
#@ _IS_INNINGS_PITCHED_


# Functions to check whether a string looks like a date in various
# common formats.  All permit the year to be 2 or 4 digits.  All permit
# delimiters to be any nondigit character.

# Each returns undef if date doesn't match the pattern, otherwise returns
# a reference to an array containing the year, month, and day parts.
# Does not perform bounds testing on the parts.

#@ _IS_ISO_DATE_
def is_iso_date(val):
  m = re.match('^(\d{2,4})\D(\d{1,2})\D(\d{1,2})$', val)
  return [int(m.group(1)),  int(m.group(2)), int(m.group(3))] if m else None
#@ _IS_ISO_DATE_

#@ _IS_MMDDYY_DATE_
def is_mmddyy_date(val):
  m = re.match('^(\d{1,2})\D(\d{1,2})\D(\d{2,4})$', val)
  return [int(m.group(3)),  int(m.group(1)), int(m.group(2))] if m else None
#@ _IS_MMDDYY_DATE_

#@ _IS_DDMMYY_DATE_
def is_ddmmyy_date(val):
  m = re.match('^(\d{1,2})\D(\d{1,2})\D(\d{2,4})$', val)
  return [int(m.group(3)),  int(m.group(2)), int(m.group(1))] if m else None
#@ _IS_DDMMYY_DATE_

# Functions to check whether a string looks like a time in 24-hour
# format, or 12-hour format with an optional AM/PM suffix.  (Note that a
# 12-hour time like 12:00:00 PM becomes a 24-hour time like 12:00:00, not
# 24:00:00. And 12:xx:xx AM is 00:xx:xx in 24-hour time)
# The hour can be 1 or 2 digits.  The minute and second must be two digits.
# Delimiters can any nondigit character.

#@ _IS_24HR_TIME_
def is_24hr_time(val):
  m = re.match('^(\d{1,2})\D(\d{2})\D(\d{2})$', val)
  if m is None:
    return None
  return[int(m.group(1)), int(m.group(2)), int(m.group(3))]
#@ _IS_24HR_TIME_

#@ _IS_AMPM_TIME_
def is_ampm_time(val):
  m = re.match('^(\d{1,2})\D(\d{2})\D(\d{2})(?:\s*(AM|PM))?$', val, flags = re.I)
  if m is None:
    return None
  (hour, min, sec) = (int(m.group(1)), (m.group(2)), (m.group(3)))
  # supply missing seconds
  sec = '00' if sec is None else sec
  if hour == 12 and (m.group(4) is None or m.group(4).upper() == "AM"):
    hour = '00' # 12:xx:xx AM times are 00:xx:xx
  elif int(hour) < 12 and (m.group(4) is not None) and m.group(4).upper() == "PM":
    hour = hour + 12 # PM times other than 12:xx:xx
  return [hour, min, sec] # return hour, minute, second
#@ _IS_AMPM_TIME_

# Determine whether a year is a leap year.  Requires 4-digit
# year value (e.g., "1993", not "93").

#@ _IS_LEAP_YEAR_
def is_leap_year(year):
  return ((year % 4 == 0) and ((year % 100 != 0) or (year % 400 == 0) ) )
#@ _IS_LEAP_YEAR_


# Given an array of integers representing year, month, and day of a date,
# determine whether the date is valid.

#@ _IS_VALID_DATE_
def is_valid_date(year, month, day):
  if year < 0 or month < 0 or day < 1:
    return 0
  if year > 9999 or month > 12 or day > days_in_month(year, month):
    return 0
  return 1
#@ _IS_VALID_DATE_


# Given an array of integers representing hour, minute, and second,
# determine whether the time is valid.

#@ _IS_VALID_TIME_
def is_valid_time(hour, minute, second):
  if hour < 0 or minute < 0 or second < 0:
    return 0
  if hour > 23 or minute > 59 or second > 59:
    return 0
  return 1
#@ _IS_VALID_TIME_


# Convert 2-digit year to 4 digits (return unchanged if not 2-digits).
# The optional second argument indicates the transition point at which
# values change from 2000-based to 1900-based.  The default is to switch
# at 70, like MySQL.  (Thus 00..69 -> 2000..2069 and 70..99 -> 1970..1999)

#@ _YY_TO_YYYY_
def yy_to_yyyy(year, transition_point = 70):
  if year < 100:
    year += 1900 if year >= transition_point else 2000
  return year
#@ _YY_TO_YYYY_


# Given year and month, return the number of days in the month.  Year
# value must be in 4-digit form or the leap-year test won't be correct.

#@ _DAYS_IN_MONTH_
def days_in_month(year, month):
  day_tbl = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
  days = day_tbl[month - 1]

  if month == 2 and is_leap_year(year):
    days += 1
  return days
#@ _DAYS_IN_MONTH_
