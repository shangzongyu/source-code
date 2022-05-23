#!/usr/bin/python3
# connect2.py: show other ways to connect to the MySQL server

# * Use a dictionary to specify connection arguments
# * How to specify a port number or Unix domain socket path explicitly.

import mysql.connector

# Use a dictionary to specify connection arguments

try:
#@ _FRAG_DICTIONARY_
  conn_params = {
    "database": "cookbook",
    "host": "localhost",
    "user": "cbuser",
    "password": "cbpass",
  }
  conn = mysql.connector.connect(**conn_params)
  print("Connected")
#@ _FRAG_DICTIONARY_
except:
  print("Cannot connect to server")
else:
  conn.close()
  print("Disconnected")

# Set the port explicitly

try:
#@ _FRAG_PORT_
  conn_params = {
    "database": "cookbook",
    "host": "127.0.0.1",
    "port": 3307,
    "user": "cbuser",
    "password": "cbpass",
  }
  conn = mysql.connector.connect(**conn_params)
#@ _FRAG_PORT_
except:
  print("Cannot connect to server")
else:
  print("Connected")
  conn.close()
  print("Disconnected")

# Set the socket file explicitly

try:
#@ _FRAG_SOCKET_
  conn_params = {
    "database": "cookbook",
    "unix_socket": "/var/tmp/mysql.sock",
    "user": "cbuser",
    "password": "cbpass",
  }
  conn = mysql.connector.connect(**conn_params)
  print("Connected")
#@ _FRAG_SOCKET_
except:
  print("Cannot connect to server")
else:
  conn.close()
  print("Disconnected")
