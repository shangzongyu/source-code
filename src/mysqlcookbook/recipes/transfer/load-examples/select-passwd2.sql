# select-passwd2.sql

# export contents of passwd table to passwd.txt as CSV, CRLF-terminated file

#@ _SELECT_CSV_
SELECT * FROM passwd INTO OUTFILE '/tmp/passwd.txt'
FIELDS TERMINATED BY ',' ENCLOSED BY '"'
LINES TERMINATED BY '\r\n';
#@ _SELECT_CSV_
