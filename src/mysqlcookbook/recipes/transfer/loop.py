#!/usr/bin/python3
# loop.py: Typical input-processing loop.

# Assumes tab-delimited, linefeed-terminated input lines.

import sys

for line in sys.stdin:
    line = line.rstrip()
    # split line at tabs, preserving all fields
    values = line.split("\t")
    for val in values: # iterate through fields in line
        # ... test val here ...
        pass
