#!/usr/bin/python3
# add_insect.py: demonstrate client-side insert_id() cursor method
# for getting the most recent AUTO_INCREMENT value.

import mysql.connector
import cookbook

conn = cookbook.connect()

try:
#@ _INSERT_ID_
  cursor = conn.cursor()
  cursor.execute('''
                 INSERT INTO insect (name,date,origin)
                 VALUES('moth','2014-09-14','windowsill')
                 ''')
  seq = cursor.lastrowid
#@ _INSERT_ID_
  cursor.close()
  conn.commit()
  print("seq: %d" % seq)
except mysql.connector.Error as e:
  print("Oops, the statement failed")
  print("Error: %s" % e)

conn.close()
