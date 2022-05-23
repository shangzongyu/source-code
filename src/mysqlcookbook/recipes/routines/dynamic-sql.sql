# dynamic-sql.sql: Demonstrate use of helper routines for executing
# dynamically generated SQL statements.

SET @tbl_name = 'mytbl';
SET @val = 143;
DROP TABLE mytbl;

#@ _EXAMPLE_1_
SET @stmt = CONCAT('CREATE TABLE ',@tbl_name,' (i INT)');
PREPARE stmt FROM @stmt;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;
SET @stmt = CONCAT('INSERT INTO ',@tbl_name,' (i) VALUES(',@val,')');
PREPARE stmt FROM @stmt;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;
#@ _EXAMPLE_1_

DROP TABLE mytbl;
#@ _EXAMPLE_2_
CALL exec_stmt(CONCAT('CREATE TABLE ',@tbl_name,' (i INT)'));
CALL exec_stmt(CONCAT('INSERT INTO ',@tbl_name,' (i) VALUES(',@val,')'));
#@ _EXAMPLE_2_

DROP TABLE mytbl;
#@ _EXAMPLE_3_
SET @tbl_name = quote_identifier(@tbl_name);
SET @val = QUOTE(@val);
CALL exec_stmt(CONCAT('CREATE TABLE ',@tbl_name,' (i INT)'));
CALL exec_stmt(CONCAT('INSERT INTO ',@tbl_name,' (i) VALUES(',@val,')'));
#@ _EXAMPLE_3_
