#!/usr/bin/python
# int_print.py: print time intervals in hours, minutes, seconds

import mysql.connector
import cookbook

conn = cookbook.connect()

#@ _TIME_COMPONENTS_
def time_components(time_in_secs):
  if time_in_secs < 0:
    sign = "-"
    time_in_secs = -time_in_secs
  else:
    sign = ""
  hours = int(time_in_secs / 3600)
  minutes = int((time_in_secs / 60)) % 60
  seconds = time_in_secs % 60
  return sign, hours, minutes, seconds
#@ _TIME_COMPONENTS_

try:
#@ _PRINT_INTERVALS_
  stmt = "SELECT t1, t2, TIME_TO_SEC(t2) - TIME_TO_SEC(t1) FROM time_val"
  cursor = conn.cursor()
  cursor.execute(stmt)
  for (t1, t2, interval) in cursor:
    (sign, hours, minutes, seconds) = time_components(interval)
    print("t1 = %s, t2 = %s, interval = %s%d h, %d m, %d s"
          % (t1, t2, sign, hours, minutes, seconds))
  cursor.close()
#@ _PRINT_INTERVALS_
except mysql.connector.Error as e:
  print("Error: %s" % e)

conn.close()
