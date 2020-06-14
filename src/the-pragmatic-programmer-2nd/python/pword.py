#!/usr/bin/python

import string

file = open('/etc/passwd', 'r')
for line in file.readlines():
    print string.splitfields(line,':')[4]
file.close()



