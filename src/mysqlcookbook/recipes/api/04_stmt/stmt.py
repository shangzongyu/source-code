#!/usr/bin/python3
# stmt.py: demonstrate statement processing in Python
# (without placeholders)

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

print("Fetch rows with fetchone")
try:
#@ _FETCHONE_
  cursor = conn.cursor()
  cursor.execute("SELECT id, name, cats FROM profile")
  while True:
    row = cursor.fetchone()
    if row is None:
      break
    print("id: %s, name: %s, cats: %s" % (row[0], row[1], row[2]))
  print("Number of rows returned: %d" % cursor.rowcount)
  cursor.close()
#@ _FETCHONE_
except mysql.connector.Error as e:
  print("Oops, the statement failed")
  print("Error: %s" % e)

# Note: Following loop would be shorter if written like this:
#  for row in cursor:
# But don't do that because surrounding text in book discusses how to
# use rows as a direct-access array following the fetch operation.

print("Fetch rows with fetchall")
try:
#@ _FETCHALL_
  cursor = conn.cursor()
  cursor.execute("SELECT id, name, cats FROM profile")
  rows = cursor.fetchall()
  for row in rows:
    print("id: %s, name: %s, cats: %s" % (row[0], row[1], row[2]))
  print("Number of rows returned: %d" % cursor.rowcount)
  cursor.close()
#@ _FETCHALL_
except mysql.connector.Error as e:
  print("Oops, the statement failed")
  print("Error: %s" % e)

print("Fetch rows using cursor as iterator")
try:
#@ _CURSOR_ITERATOR_
  cursor = conn.cursor()
  cursor.execute("SELECT id, name, cats FROM profile")
  for (id, name, cats) in cursor:
    print("id: %s, name: %s, cats: %s" % (id, name, cats))
  print("Number of rows returned: %d" % cursor.rowcount)
  cursor.close()
#@ _CURSOR_ITERATOR_
except mysql.connector.Error as e:
  print("Oops, the statement failed")
  print("Error: %s" % e)

print("Execute UPDATE statement (no placeholders)")
try:
#@ _DO_1_
  cursor = conn.cursor()
  cursor.execute("UPDATE profile SET cats = cats+1 WHERE name = 'Sybil'")
  print("Number of rows updated: %d" % cursor.rowcount)
  cursor.close()
  conn.commit()
#@ _DO_1_
except mysql.connector.Error as e:
  print("Oops, the statement failed")
  print("Error: %s" % e)

conn.close()
