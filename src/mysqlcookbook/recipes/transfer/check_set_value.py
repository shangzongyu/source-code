#!/usr/bin/python3
# check_set_value.py: Wrapper to demonstrate check_set_value()
# utility function that determines whether a value is a legal
# value of a given SET column.

# Usage: check_set_value.py db_name tbl_name col_name test_value

import sys
import mysql.connector
import cookbook
from cookbook_utils import *

if len(sys.argv) != 5:
  print("Usage: check_enum_value.py db_name tbl_name col_name test_val")
  sys.exit(1)
db_name = sys.argv[1]
tbl_name = sys.argv[2]
col_name = sys.argv[3]
val = sys.argv[4]

try:
  conn = cookbook.connect()
except mysql.connector.Error as e:
  print("Error: %s" % e)
  sys.exit(1)

#@ _BULK_SET_CHECK_SETUP_
info = get_enumorset_info(conn, db_name, tbl_name, col_name)
members={}
# convert dictionary key to consistent lettercase
for v in info['values']:
  members[v.lower()] = 1
#@ _BULK_SET_CHECK_SETUP_

# If any element of the test value isn't in the SET,
# the entire value is invalid

#@ _BULK_SET_CHECK_TEST_
valid = 1 # assume valid until we find out otherwise
for v in val.split(","):
  if v.lower() not in members:
    valid = 0
    break
#@ _BULK_SET_CHECK_TEST_

print(val),
if valid:
  print("is"),
else:
  print("is not"),
print("a member of %s.%s" % (tbl_name, col_name))

conn.close()
