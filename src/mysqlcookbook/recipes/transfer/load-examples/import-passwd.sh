#!/bin/sh

# This script assumes connection parameters are in ~/.my.cnf.

DB=cookbook

# test for reading /etc/passwd, without the password column

cut -d: -f1,3- /etc/passwd > passwd.txt

mysql $DB <<EOF
DELETE FROM passwd;
EOF

mysqlimport --local --fields-terminated-by=: cookbook passwd.txt

mysql -t cookbook <<EOF
SELECT * from passwd;
EOF
