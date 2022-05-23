#!/usr/bin/python3
# see.py: Print nonprinting chars sensibly.

import sys

def see(f):
  while True:
    c = f.read(1)
    if len(c) == 0:
      return
    o = ord(c)
    if o == 10:         # 10 = linefeed
      c = "$\n"
    elif o < 32:        # control char? (32 = space)
      c = "^%c" % (o+64)
    elif o == 92:       # \ -> \\ (92 = backslash)
      c = "\\\\"
    elif o >= 127:      # DEL and non-ASCII as octal
      c = "\\%3o" % o
    sys.stdout.write(c)

# Read stdin if no files were named, otherwise read each named file

if len(sys.argv) < 2:
  see(sys.stdin)
else:
  for name in sys.argv[1:]:
    f = open(name, "r")
    see(f)
    f.close()
