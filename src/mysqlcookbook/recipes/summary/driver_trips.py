#!/usr/bin/python3
# driver_trips.py: summarize miles per driver and show a list for each
# driver of the trips they took.

# Two approaches are demonstrated:
# - Two queries.  First query retrieves the summary values, second the
#   list entries.  Print the list entries, preceding the list for each
#   driver with the corresponding summary information.
# - Single query to retrieve the list entries.  Iterate through the list
#   once to compute the summary values, and a second time to print the
#   summary and list information.

import mysql.connector
import cookbook

try:
  conn = cookbook.connect()
  print("Summary, method 1:")
#@ _TWO_QUERY_
  # select total miles per driver and construct a dictionary that
  # maps each driver name to days on the road and miles driven
  name_map = {}
  cursor = conn.cursor()
  cursor.execute('''
                 SELECT name, COUNT(name), SUM(miles)
                 FROM driver_log GROUP BY name
                 ''')
  for (name, days, miles) in cursor:
    name_map[name] = (days, miles)

  # select trips for each driver and print the report, displaying the
  # summary entry for each driver prior to the list of trips
  cursor.execute('''
                 SELECT name, trav_date, miles
                 FROM driver_log ORDER BY name, trav_date
                 ''')
  cur_name = ""
  for (name, trav_date, miles) in cursor:
    if cur_name != name:  # new driver; print driver's summary info
      print("Name: %s; days on road: %d; miles driven: %d" %
            (name, name_map[name][0], name_map[name][1]))
      cur_name = name
    print("  date: %s, trip length: %d" % (trav_date, miles))
  cursor.close()
#@ _TWO_QUERY_

  print("")
  print("Summary, method 2:")
#@ _ONE_QUERY_
  # get list of trips for the drivers
  cursor = conn.cursor()
  cursor.execute('''
                 SELECT name, trav_date, miles FROM driver_log
                 ORDER BY name, trav_date
                 ''')
  # fetch rows into data structure because we
  # must iterate through them multiple times
  rows = cursor.fetchall()
  cursor.close()

  # iterate through rows once to construct a dictionary that
  # maps each driver name to days on the road and miles driven
  # (the dictionary entries are lists rather than tuples because
  # we need mutable values that can be modified in the loop)
  name_map = {}
  for (name, trav_date, miles) in rows:
    if name not in name_map: # initialize entry if nonexistent
      name_map[name] = [0, 0]
    name_map[name][0] += 1     # count days
    name_map[name][1] += miles # sum miles

  # iterate through rows again to print the report, displaying the
  # summary entry for each driver prior to the list of trips
  cur_name = ""
  for (name, trav_date, miles) in rows:
    if cur_name != name:  # new driver; print driver's summary info
      print("Name: %s; days on road: %d; miles driven: %d" %
            (name, name_map[name][0], name_map[name][1]))
      cur_name = name
    print("  date: %s, trip length: %d" % (trav_date, miles))
#@ _ONE_QUERY_

except mysql.connector.Error as e:
  print("Error: %s" % e)
else:
  conn.close()
