#!/usr/bin/python3
# placeholder.py: demonstrate statement processing in Python
# (with placeholders)

import sys
import mysql.connector
import cookbook

try:
  conn = cookbook.connect()
except mysql.connector.Error as e:
  print("Cannot connect to server")
  print("Error code: %s" % e.errno)
  print("Error message: %s" % e.msg)
  sys.exit(1)

print("Execute INSERT statement using placeholders")
try:
#@ _EXECUTE_PLACEHOLDER_1_
  cursor = conn.cursor()
  cursor.execute('''
                 INSERT INTO profile (name,birth,color,foods,cats)
                 VALUES(%s,%s,%s,%s,%s)
                 ''', ("De'Mont", "1973-01-12", None, "eggroll", 4))
  cursor.close()
  conn.commit()
#@ _EXECUTE_PLACEHOLDER_1_
except mysql.connector.Error as e:
  print("Oops, the statement failed")
  print("Error: %s" % e)

print("Execute SELECT statement using placeholders")
try:
#@ _EXECUTE_PLACEHOLDER_2_
  cursor = conn.cursor()
  cursor.execute("SELECT id, name, cats FROM profile WHERE cats = %s", (2,))
  for (id, name, cats) in cursor:
    print("id: %s, name: %s, cats: %s" % (id, name, cats))
  cursor.close()
#@ _EXECUTE_PLACEHOLDER_2_
except mysql.connector.Error as e:
  print("Oops, the statement failed")
  print("Error: %s" % e)

conn.close()

