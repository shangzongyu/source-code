#!/usr/bin/python3
# get_rs_meta.py: run a statement and display its result set metadata

# The program runs a default statement, which can be overridden by supplying
# a statement as an argument on the command line.

import sys
import mysql.connector
from mysql.connector import FieldType
import cookbook

#@ _DEFAULT_STATEMENT_
stmt = "SELECT name, birth FROM profile"
#@ _DEFAULT_STATEMENT_
# override statement with command line argument if one was given
if len(sys.argv) > 1:
  stmt = sys.argv[1]

try:
  conn = cookbook.connect()
except mysql.connector.Error as e:
  print("Error code: %s" % e.errno)
  print("Error message: %s" % e.msg)
  sys.exit(1)

try:
#@ _DISPLAY_METADATA_
  print("Statement: %s" % stmt)
  # buffer cursor so that rowcount has usable value
  cursor = conn.cursor(buffered=True)
  cursor.execute(stmt)
  # metadata information becomes available at this point ...
  print("Number of rows: %d" % cursor.rowcount)
  if cursor.with_rows:
    ncols = len(cursor.description)
  else:
    ncols = 0 # no result set
  print("Number of columns: %d" % ncols)
  if ncols == 0:
    print("Note: statement has no result set")
  else:
    for i, col_info in enumerate(cursor.description):
      # print name, then other information
      name, type, _, _, _, _, nullable, flags, *_ = col_info
      print("--- Column %d (%s) ---" % (i, name))
      print("Type:     %d (%s)" % (type, FieldType.get_info(type)))
      print("Nullable: %d" % (nullable or 0))
      print("Flags:    %d" % (flags))
  cursor.close()
#@ _DISPLAY_METADATA_
except mysql.connector.Error as e:
  print("Error code: %s" % e.errno)
  print("Error message: %s" % e.msg)

conn.close()
