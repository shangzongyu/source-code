#!/usr/bin/python3
# disp_origin.py: display list of distinct origin values from the insect
# table, numbering the output rows.

import mysql.connector
import cookbook

conn = cookbook.connect()

try:
#@ _FRAG_
  cursor = conn.cursor()
  cursor.execute("SELECT DISTINCT origin FROM insect")
  count = 0
  for row in cursor:
    count += 1
    print("%d %s" % (count, row[0]))
  cursor.close()
#@ _FRAG_
except mysql.connector.Error as e:
  print("Error: %s" % e)

conn.close()
