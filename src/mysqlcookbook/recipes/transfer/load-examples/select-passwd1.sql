# select-passwd1.sql

# export contents of passwd table to passwd.txt as tab-delimited,
# linefeed-terminated file

#@ _SELECT_TAB_
SELECT * FROM passwd INTO OUTFILE '/tmp/passwd.txt';
#@ _SELECT_TAB_
