#!/usr/bin/python3
# get_column_names.py: wrapper to demonstrate get_column_names()
# utility routine

# Assumes that the "image" table has been created!

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

print("Using get_column_names()")
print("Columns in %s.%s table:" % (db_name, tbl_name))
names = get_column_names(conn, db_name, tbl_name)
print(", ".join(names))

# construct "all but" statement
print("Construct statement to select all but data column:")
#@ _ALL_BUT_
names = get_column_names(conn, db_name, tbl_name)
# remove "data" from list of names; use try because remove
# raises an exception if value isn't in list
try:
  names.remove("data")
except:
  pass
stmt = "SELECT `%s` FROM `%s`.`%s`" % ("`, `".join(names), db_name, tbl_name)
#@ _ALL_BUT_
print(stmt)

conn.close()
