#!/usr/bin/python3
# cmdline.py: demonstrate command-line option parsing in Python

import sys
import getopt
import mysql.connector

try:
  opts, args = getopt.getopt(sys.argv[1:],
                             "h:p:u:",
                             [
                               "host=",
                                "password=",
                                "user="
                             ])
except getopt.error as e:
  # for errors, print program name and text of error message
  print("%s: %s" % (sys.argv[0], e))
  sys.exit(1)

# default connection parameter values
conn_params = {
  "database": "cookbook",
  "host": "",
  "user": "",
  "password": ""
}

# iterate through options, extracting whatever values are present
for opt, arg in opts:
  if opt in ("-h", "--host"):
    conn_params["host"] = arg
  elif opt in ("-p", "--password"):
    conn_params["password"] = arg
  elif opt in ("-u", "--user"):
    conn_params["user"] = arg

# any nonoption arguments remain in args
# and can be processed here as necessary

try:
  conn = mysql.connector.connect(**conn_params)
  print("Connected")
except mysql.connector.Error as e:
  print("Cannot connect to server")
  print("Error code: %s" % e.errno)
  print("Error message: %s" % e.msg)
else:
  conn.close()
  print("Disconnected")
