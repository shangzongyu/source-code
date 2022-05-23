#!/usr/bin/python3
# load_amazon_reviews.py: Utility to load Amazon review for examples in the chapter 7.

# Pre-requisites: 
# 1. $ curl -L -s http://deepyeti.ucsd.edu/jianmo/amazon/categoryFilesSmall/Appliances_5.json.gz | gunzip > /tmp/Appliances_5.json
# 2. $ mysql cookbook < ../tables/reviews.sql

# Usage: ./load_amazon_reviews.py /tmp/Appliances_5.json

import os
import sys
import mysql.connector
import cookbook

if len(sys.argv) != 2:
  print("Usage: ./load_amazon_reviews.py /tmp/Appliances_5.json")
  sys.exit(1)

filepath = sys.argv[1]
if not os.path.isfile(filepath):
  print("File path {} does not exist. Exiting...".format(filepath))
  sys.exit(1)

try:
  conn = cookbook.connect()
  cur = conn.cursor(prepared=True)
except mysql.connector.Error as e:
  print("Error: %s" % e)
  sys.exit(1)

sql = "INSERT INTO reviews(id, appliences_review) VALUES (0,%s)"

with open(filepath) as file:
  line = file.readline()
  while line:
    cur.execute(sql, (line,))
    conn.commit()
    line = file.readline()

cur.close()
conn.close()
sys.exit(0)
