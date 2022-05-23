# cookbook.py: library file with utility method for connecting to MySQL
# using the Connector/Python module

import mysql.connector

conn_params = {
  "database": "cookbook",
  "host": "localhost",
  "user": "cbuser",
  "password": "cbpass",
}

# Establish a connection to the cookbook database, returning a connection
# object.  Raise an exception if the connection cannot be established.

def connect():
  return mysql.connector.connect(**conn_params)
