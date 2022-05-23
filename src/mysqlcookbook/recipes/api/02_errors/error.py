#!/usr/bin/python3
# error.py: demonstrate MySQL error handling

import mysql.connector

#@ _FRAG_
conn_params = {
  "database": "cookbook",
  "host": "localhost",
  "user": "baduser",
  "password": "badpass"
}

try:
  conn = mysql.connector.connect(**conn_params)
  print("Connected")
except mysql.connector.Error as e:
  print("Cannot connect to server")
  print("Error code: %s" % e.errno)
  print("Error message: %s" % e.msg)
  print("Error SQLSTATE: %s" % e.sqlstate)
#@ _FRAG_
else:
  conn.close()
  print("Disconnected")
