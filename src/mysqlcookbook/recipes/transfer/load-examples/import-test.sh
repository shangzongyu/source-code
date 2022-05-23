#!/bin/sh

# test import of tab-delimited data

echo "read tab-delimited"
mysql -t cookbook <<EOF
DELETE FROM mytbl
EOF

cp data-tab.txt mytbl.txt
mysqlimport --local cookbook mytbl.txt

mysql -t cookbook <<EOF
SELECT * from mytbl;
EOF

echo "read tab-delimited (crlf)"
mysql -t cookbook <<EOF
DELETE FROM mytbl
EOF

cp data-tab-crlf.txt mytbl.txt
#mysqlimport --local --lines-terminated-by='\r\n' cookbook mytbl.txt
mysqlimport --local --lines-terminated-by=0x0d0a cookbook mytbl.txt

mysql -t cookbook <<EOF
SELECT * from mytbl;
EOF

# test import of tab-delimited data (explicit format specifiers)

echo "read tab-delimited (explicit format specifiers)"
mysql -t cookbook <<EOF
DELETE FROM mytbl
EOF

cp data-tab.txt mytbl.txt
mysqlimport --local --fields-terminated-by='\t' --lines-terminated-by='\n' \
  cookbook mytbl.txt

mysql -t cookbook <<EOF
SELECT * from mytbl;
EOF

# test import of CSV data

echo "read CSV (newline-terminated)"
mysql -t cookbook <<EOF
DELETE FROM mytbl
EOF

cp data-csv.txt mytbl.txt
mysqlimport --local --fields-terminated-by=, --fields-enclosed-by='"' \
  cookbook mytbl.txt

mysql -t cookbook <<EOF
SELECT * from mytbl;
EOF

# test import of CSV data (crlf-terminated)

echo "read CSV (crlf-terminated)"
mysql -t cookbook <<EOF
DELETE FROM mytbl
EOF

cp data-csv-crlf.txt mytbl.txt
mysqlimport --local --fields-terminated-by=, --fields-enclosed-by='"' \
  --lines-terminated-by='\r\n' cookbook mytbl.txt

mysql -t cookbook <<EOF
SELECT * from mytbl;
EOF

# test import of colon-delimited (cr-terminated) data

echo "read colon-delimited (cr-terminated)"
mysql -t cookbook <<EOF
DELETE FROM mytbl
EOF

cp data-colon-cr.txt mytbl.txt
mysqlimport --local --fields-terminated-by=: --lines-terminated-by='\r' \
  cookbook mytbl.txt

mysql -t cookbook <<EOF
SELECT * from mytbl;
EOF
