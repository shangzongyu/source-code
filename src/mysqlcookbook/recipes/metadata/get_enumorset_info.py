#!/usr/bin/python3
# get_enumorset_info.py: wrapper to demonstrate get_enumorset_info()
# utility routine.

# Usage: get_enumorset_info.py db_name tbl_name col_name

import sys
import mysql.connector
import cookbook
from cookbook_utils import *


if len(sys.argv) != 4:
  print("Usage: get_enumorset_info.py db_name tbl_name col_name")
  sys.exit(1)
db_name = sys.argv[1]
tbl_name = sys.argv[2]
col_name = sys.argv[3]

try:
  conn = cookbook.connect()
except mysql.connector.Error as e:
  print("Error code: %s" % e.errno)
  print("Error message: %s" % e.msg)
  sys.exit(1)

#@ _USE_FUNCTION_
info = get_enumorset_info(conn, db_name, tbl_name, col_name)
print("Information for " + db_name + "." + tbl_name + "." + col_name + ":")
if info is None:
  print("No information available (not an ENUM or SET column?)")
else:
  print("Name: %s" % info["name"])
  print("Type: %s" % info["type"])
  print("Legal values: %s" % ",".join(info["values"]))
  if info["nullable"]:
    print("Nullable: yes")
  else:
    print("Nullable: no")
  if info["default"] is None:
    print("Default value: NULL")
  else:
    print("Default value: %s" % info["default"])
#@ _USE_FUNCTION_

conn.close()
