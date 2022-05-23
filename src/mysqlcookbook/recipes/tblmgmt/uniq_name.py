#!/usr/bin/python3
# uniq_name.py: show how to use PID to create table name

#@ _GENERATE_NAME_WITH_PID_1_
import os
#@ _GENERATE_NAME_WITH_PID_1_

pid = os.getpid()
print("PID: %s" % pid)
#@ _GENERATE_NAME_WITH_PID_2_
tbl_name = "tmp_tbl_%d" % os.getpid()
#@ _GENERATE_NAME_WITH_PID_2_
print("Table name: %s" % tbl_name)
