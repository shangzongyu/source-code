#!/usr/bin/python3
# affected_rows.py

import sys
import mysql.connector
import cookbook

try:
  conn = cookbook.connect()
except mysql.connector.Error as e:
  print("Error code: %s" % e.errno)
  print("Error message: %s" % e.msg)
  sys.exit(1)

stmt = "UPDATE profile SET cats = cats+1 WHERE name = 'Sybil'"
try:
#@ _FRAG_
  cursor = conn.cursor()
  cursor.execute(stmt)
  print("Number of rows affected: %d" % cursor.rowcount)
  cursor.close()
#@ _FRAG_
except mysql.connector.Error as e:
  print("Error code: %s" % e.errno)
  print("Error message: %s" % e.msg)
  sys.exit(1)

conn.close()

# illustrate how to get rows-matched counts rather than rows-changed counts

#@ _IMPORT_CONSTANTS_
from mysql.connector.constants import ClientFlag
#@ _IMPORT_CONSTANTS_

try:
#@ _FOUND_ROWS_
  conn = mysql.connector.connect(
    database="cookbook",
    host="localhost",
    user="cbuser",
    password="cbpass",
    client_flags=[ClientFlag.FOUND_ROWS]
  )
#@ _FOUND_ROWS_
except mysql.connector.Error as e:
  print("Error code: %s" % e.errno)
  print("Error message: %s" % e.msg)
  sys.exit(1)

# this statement changes no rows, but the row count should still
# be nonzero due to the use of rows-matched counts

stmt = "UPDATE limbs SET arms = 0 WHERE arms = 0"

try:
  cursor = conn.cursor()
  cursor.execute(stmt)
  print("Number of rows affected: %d" % cursor.rowcount)
  cursor.close()
except mysql.connector.Error as e:
  print("Error code: %s" % e.errno)
  print("Error message: %s" % e.msg)
  sys.exit(1)

conn.close()
