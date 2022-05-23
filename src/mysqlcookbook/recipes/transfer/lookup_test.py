#!/usr/bin/python3
# lookup_test.py: Illustrate various ways to use a lookup table
# to determine whether or not input values are listed in the table.

# The methods check values listed in a list.  You'd probably be more
# likely to use the inner part of each loop in an input processing loop
# that reads lines from a file.

# The lookup table name is determined by tbl_name (default: "lookup_table").
# Change the variable value to use a different table.

# The tests are case sensitive.  To perform case-insensitive tests,
# convert the lookup values to lowercase, then test lowercased input
# values against them.  (Uppercase would work, too.)

import sys
import mysql.connector
import cookbook
from cookbook_utils import *

tbl_name = "lookup_table"

try:
  conn = cookbook.connect()
  cursor = conn.cursor()
except mysql.connector.Error as e:
  print("Error: %s" % e)
  sys.exit(1)

# Create and populate the lookup table with a set of values

lookup_values = ["pig", "cat", "duck", "goat", "dog"];

cursor.execute(f"DROP TABLE IF EXISTS {tbl_name}");
cursor.execute(f"CREATE TABLE {tbl_name} (val CHAR(10))");
for val in lookup_values:
  cursor.execute(f"INSERT INTO {tbl_name} (val) VALUES(%(val)s)", {'val': val})

print("Legal lookup values:", lookup_values)

# The set of "input" values to be checked against the lookup table

input = ["snake", "dog", "sheep", "cat", "snake", "dog", "snake"]

valid = 0

# Method 1: Issue individual query to check each input value

print("Issue lookup query for each input value:")

for val in input:
#@ _QUERY_PER_VALUE_
  cursor.execute(f"SELECT COUNT(*) FROM {tbl_name} WHERE val = %(val)s", {'val': val})
  valid = cursor.fetchone()[0]
#@ _QUERY_PER_VALUE_
  print("Value:", val, "(", ("good" if valid > 0 else "bad"), ")")

# Method 2: Read contents of lookup table into a dictionary, using each value
# as a dictionary key.  Check input values by performing key existence test.

print("Read lookup table into dictionary, use dictionary to check input values:")

#@ _READ_LOOKUP_TABLE_
members = {}  # hash for lookup values
cursor.execute(f"SELECT val FROM {tbl_name}");
rows = cursor.fetchall()
for row in rows:
  members[row[0]] = 1;
#@ _READ_LOOKUP_TABLE_

for val in input:
#@ _LOOKUP_VIA_DICTIONARY_KEY_
  valid = True if val in members else False
#@ _LOOKUP_VIA_DICTIONARY_KEY_
  print("Value:", val, "(", ("good" if valid > 0 else "bad"), ")")

# Method 3: Use a dictionary as a cache of those input values that have been
# seen.  Look up each value as it's encountered, storing the value as
# a dictionary key, and true/false as the dictionary value to indicate whether or
# not the value was present in the table.  The next time the value is
# encountered, it'll be in the dictionary and can be checked without issuing
# a query.

print("Dictionary as cache of seen input values:")

#@ _DICTIONARY_AS_CACHE_1_
members = {}  # dictionary for lookup values
#@ _DICTIONARY_AS_CACHE_1_
for val in input:
#@ _DICTIONARY_AS_CACHE_2_
  if val not in members: # haven't seen this value yet
    cursor.execute(f"SELECT COUNT(*) FROM {tbl_name} WHERE val = %(val)s", {'val': val})
    count = cursor.fetchone()[0]
    # store true/false to indicate whether value was found
    members[val] = True if count > 0 else False
  valid = members[val]
#@ _DICTIONARY_AS_CACHE_2_
  print("Value:", val, "(", ("good" if valid > 0 else "bad"), ")")

cursor.close()
conn.close()
