#!/usr/bin/python3
# harness2.py: test harness for cookbook.py library

# Does not catch exceptions, so this script simply dies if
# a connect error occurs.

import cookbook

#@ _FRAG_
conn = cookbook.connect()
print("Connected")
conn.close()
print("Disconnected")
#@ _FRAG_

