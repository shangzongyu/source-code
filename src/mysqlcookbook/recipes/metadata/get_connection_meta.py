#!/usr/bin/python3
# get_connection_meta.py: get connection metadata

import sys
import mysql.connector
import cookbook

try:
  conn = cookbook.connect()
except mysql.connector.Error as e:
  print("Error code: %s" % e.errno)
  print("Error message: %s" % e.msg)
  sys.exit(1)

try:
#@ _CURRENT_DATABASE_
  cursor = conn.cursor()
  cursor.execute("SELECT DATABASE()")
  row = cursor.fetchone()
  cursor.close()
  if row is None or len(row) == 0 or row[0] is None:
    db = "(no database selected)"
  else:
    db = row[0]
  print("Default database: %s" % db)
#@ _CURRENT_DATABASE_
except mysql.connector.Error as e:
  print("Error code: %s" % e.errno)
  print("Error message: %s" % e.msg)
  sys.exit(1)

conn.close()
