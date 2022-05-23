#!/usr/bin/python3
# get_column_info.py: wrapper to demonstrate get_column_info()
# utility routine

# Assumes that you've created the "image" table!

import sys
import mysql.connector
import cookbook
from cookbook_utils import *

db_name = "cookbook"
tbl_name = "image"

try:
  conn = cookbook.connect()
except mysql.connector.Error as e:
  print("Error code: %s" % e.errno)
  print("Error message: %s" % e.msg)
  sys.exit(1)

print("Using get_column_info()")
print("Column information for %s.%s table:" % (db_name, tbl_name))
info = get_column_info(conn, db_name, tbl_name)
for col_name in info:
  col_info = info[col_name]
  print("  Column: %s" % col_name)
  for col_info_key in col_info:
    print("    %s: %s" % (col_info_key, col_info[col_info_key]))

conn.close()
