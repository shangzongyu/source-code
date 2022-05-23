# exec_stmt.sql

# Given a statement as a string, prepares and executes it.
# The statement does not permit placeholders. It'd be possible
# to define exec_stmt{1,2,3,...} that permit 1,2,3,... data values.

# Uses a user-defined variable (@_stmt_str) because PREPARE cannot
# prepare a statement from a local routine variable.

DROP PROCEDURE IF EXISTS exec_stmt;
delimiter $$
#@ _DEFINITION_
CREATE PROCEDURE exec_stmt(stmt_str TEXT)
BEGIN
  SET @_stmt_str = stmt_str;
  PREPARE stmt FROM @_stmt_str;
  EXECUTE stmt;
  DEALLOCATE PREPARE stmt;
END;
#@ _DEFINITION_
$$
delimiter ;

CALL exec_stmt('SELECT 1');
CALL exec_stmt('SELECT DATABASE()');
