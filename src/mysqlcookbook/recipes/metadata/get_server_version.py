#!/usr/bin/python3
# get_server_version.py: get server version string and number from server

# This script demonstrates how to get the string by issuing a
# SELECT VERSION() statement.

import re
import mysql.connector
import cookbook

# Return a list consisting of the server version number in both string
# and numeric forms.

def get_server_version(conn):
  # fetch result into scalar string
  cursor = conn.cursor()
  cursor.execute("SELECT VERSION()")
  ver_str = cursor.fetchall()[0][0]
  cursor.close()
  (major, minor, patch) = ver_str.split('.')
  patch = re.sub('\D.*$', "", patch)  # strip nonnumeric suffix if present
  ver_num = int(major)*10000 + int(minor)*100 + int(patch)
  return (ver_str, ver_num)

try:
  conn = cookbook.connect()
  # get server version string and number and print them
  (ver_str, ver_num) = get_server_version(conn)
  print("Version: %s (%d)" % (ver_str, ver_num))
  conn.close()
except mysql.connector.Error as e:
  print("Error code: %s" % e.errno)
  print("Error message: %s" % e.msg)
