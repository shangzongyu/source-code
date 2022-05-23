#!/usr/bin/python3
# envshow.py: show environment values

import os

print("user: %d" % os.geteuid())
keys = sorted(os.environ.keys())
for k in keys:
  print("%s: %s" % (k, os.environ[k]))
