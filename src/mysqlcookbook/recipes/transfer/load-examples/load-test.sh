#!/bin/sh

# This script assumes connection parameters are in ~/.my.cnf.

DB=cookbook

# test for reading tab-delimited data

echo "read tab-delimited"
cp data-tab.txt mytbl.txt

mysql --local-infile -t $DB <<EOF
DELETE FROM mytbl;
#@ SAME_AS_DEFAULT_STMT
LOAD DATA LOCAL INFILE 'mytbl.txt' INTO TABLE mytbl
FIELDS TERMINATED BY '\t'
LINES TERMINATED BY '\n';
#@ SAME_AS_DEFAULT_STMT
SELECT * FROM mytbl;

DELETE FROM mytbl;
#@ _HEX_NOTATION_
LOAD DATA LOCAL INFILE 'mytbl.txt' INTO TABLE mytbl
FIELDS TERMINATED BY 0x09
LINES TERMINATED BY 0x0a;
#@ _HEX_NOTATION_
SELECT * FROM mytbl;

DELETE FROM mytbl;
LOAD DATA LOCAL INFILE 'mytbl.txt' INTO TABLE mytbl
FIELDS TERMINATED BY '\t' OPTIONALLY ENCLOSED BY '"'
LINES TERMINATED BY '\n';
SELECT * FROM mytbl;
EOF

# test for reading Windows tab-delimited data

echo "read tab-delimited (crlf)"
cp data-tab-crlf.txt mytbl.txt

mysql --local-infile -t $DB <<EOF
DELETE FROM mytbl;
#@ _WINDOWS_TAB_DELIMITED_
LOAD DATA LOCAL INFILE 'mytbl.txt' INTO TABLE mytbl
LINES TERMINATED BY '\r\n';
#@ _WINDOWS_TAB_DELIMITED_
SELECT * FROM mytbl;
EOF

# test for reading CSV data (crlf-terminated)

echo "read CSV (crlf)"
cp data-csv-crlf.txt mytbl.txt

mysql --local-infile -t $DB <<EOF
DELETE FROM mytbl;
#@ _LOAD_CSV_STMT_
LOAD DATA LOCAL INFILE 'mytbl.txt' INTO TABLE mytbl
FIELDS TERMINATED BY ',' ENCLOSED BY '"'
LINES TERMINATED BY '\r\n';
#@ _LOAD_CSV_STMT_

SELECT * FROM mytbl;
EOF

# test for reading tab-delimited data with IGNORE

echo "read tab-delimited with IGNORE"
cp data-tab.txt mytbl.txt

mysql --local-infile -t $DB <<EOF
DELETE FROM mytbl;
#@ _TAB_WITH_IGNORE_
LOAD DATA LOCAL INFILE 'mytbl.txt' INTO TABLE mytbl
IGNORE 1 LINES;
#@ _TAB_WITH_IGNORE_

SELECT * FROM mytbl;
EOF

# test for reading merge-format data (cr-terminated) with IGNORE

echo "read merge (cr) with IGNORE"
cp data-merge-cr.txt mytbl.txt

mysql --local-infile -t $DB <<EOF
DELETE FROM mytbl;
#@ _CSV_WITH_IGNORE_
LOAD DATA LOCAL INFILE 'mytbl.txt' INTO TABLE mytbl
FIELDS TERMINATED BY ',' ENCLOSED BY '"'
LINES TERMINATED BY '\r'
IGNORE 1 LINES;
#@ _CSV_WITH_IGNORE_

SELECT * FROM mytbl;
EOF

# test for reading colon-delimited (cr-terminated) data

echo "read colon-delimited (cr-terminated)"
cp data-colon-cr.txt mytbl.txt

mysql --local-infile -t $DB <<EOF
DELETE FROM mytbl;
#@ _COLON_CR_
LOAD DATA LOCAL INFILE 'mytbl.txt' INTO TABLE mytbl
FIELDS TERMINATED BY ':'
LINES TERMINATED BY '\r';
#@ _COLON_CR_
SELECT * FROM mytbl;
EOF
