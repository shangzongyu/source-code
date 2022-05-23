#!/usr/bin/python3
# connect4.py: connect to the MySQL server specifying character set

import mysql.connector

try:
#@ _FRAG_
  conn_params = {
    "database": "cookbook",
    "host": "localhost",
    "user": "cbuser",
    "password": "cbpass",
    "charset": "utf8",
  }
#@ _FRAG_
  conn = mysql.connector.connect(**conn_params)
  print("Connected")
except:
  print("Cannot connect to server")
else:
  conn.close()
  print("Disconnected")
