#!/usr/bin/python3
# dup_count.py: generate query to identify and count duplicate values

import sys

# Given database and table name and a list of one or more column
# names, return a query that can be executed to count duplicate values
# for those columns.

def make_dup_count_query(db_name, tbl_name, col_name):
  return("SELECT COUNT(*)," + ",".join(col_name) +
         "\nFROM " + db_name + "." + tbl_name +
         "\nGROUP BY " + ",".join(col_name) +
         "\nHAVING COUNT(*) > 1")

if len(sys.argv) < 4:
  print("Usage: dup_count.py db_name tbl_name col_name ...")
  sys.exit(1)

print(make_dup_count_query(sys.argv[1], sys.argv[2], sys.argv[3:]))
