#!/bin/sh
# mysql_export: given a database and table name, dump out the table
# in tab-delimited format.

if [ $# -ne 2 ]; then echo "Usage: $0 db_name tbl_name" 1>&2; exit 1; fi
DB_NAME="$1"
shift
TBL_NAME="$1"
shift
mysql -e "SELECT * FROM $TBL_NAME" --batch --skip-column-names $DB_NAME

exit 0
