#!/usr/bin/python3
# check_enum_value.py: Wrapper to demonstrate check_enum_value()
# utility function that determines whether a value is a member of
# a given ENUM column.

# Usage: check_enum_value.py db_name tbl_name col_name test_value

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

valid = check_enum_value(conn, db_name, tbl_name, col_name, val)

print(val),
if valid:
  print("is"),
else:
  print("is not"),
print("a member of %s.%s" % (tbl_name, col_name))

conn.close()
