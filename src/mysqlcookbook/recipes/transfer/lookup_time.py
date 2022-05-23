#!/usr/bin/python3
# lookup_time.py: Rough test of dictionary versus list lookups.

# - Construct a dictionary with n keys
# - Construct a list with n keys
# - Perform n lookups on each

# This is a very crude test.  Even so, we find the results are often
# striking even for n = 100000.

import time
import sys

n = 100000  # number of keys to use/lookups to perform

mydict = {}
mylist = []

for i in range(1, n+1):
  mydict[i] = 1
  mylist.append(i)

print(time.perf_counter())
print("Performing", n, "dictionary lookups...")
for i in range(1, n+1):
  if i not in mydict:
    sys.exit
print ("Done.")
print(time.perf_counter())
print("Performing", n, "list lookups...")
for i in range(1, n+1):
  if mylist.count(i) <= 0:
    sys.exit
print ("Done.")
print(time.perf_counter())
