#!/usr/bin/python3
# booksales.py: show how to use LAST_INSERT_ID(expr)

import mysql.connector
import cookbook

conn = cookbook.connect()

try:
#@ _UPDATE_COUNTER_
  cursor = conn.cursor()
  cursor.execute('''
                 INSERT INTO booksales (title,copies)
                 VALUES('The Greater Trumps',LAST_INSERT_ID(1))
                 ON DUPLICATE KEY UPDATE copies = LAST_INSERT_ID(copies+1)
                 ''')
  count = cursor.lastrowid
  cursor.close()
  conn.commit()
#@ _UPDATE_COUNTER_
  print("count: %d" % count)
except mysql.connector.Error as e:
  print("Oops, the statement failed")
  print("Error: %s" % e)

conn.close()
