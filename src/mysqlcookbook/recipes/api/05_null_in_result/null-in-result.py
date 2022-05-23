#!/usr/bin/python3

import mysql.connector
import cookbook

conn = cookbook.connect()

try:
#@ _FETCHLOOP_
  cursor = conn.cursor()
  cursor.execute("SELECT name, birth, foods FROM profile")
  for row in cursor:
    row = list(row)  # convert nonmutable tuple to mutable list
    for i, value in enumerate(row):
      if value is None:  # is the column value NULL?
        row[i] = "NULL"
    print("name: %s, birth: %s, foods: %s" % (row[0], row[1], row[2]))
  cursor.close()
#@ _FETCHLOOP_
except mysql.connector.Error as e:
  print("Oops, the statement failed")
  print("Error: %s" % e)

conn.close()
