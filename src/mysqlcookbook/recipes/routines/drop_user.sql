# drop_user.sql

# drop_user() drops a MySQL account, ignoring the error that occurs
# if the account does not exist, except to print a message that the
# error was ignored. DROP USER has no IF EXISTS clause like several
# other DROP statements; this procedure implements an equivalent effect.

# drop_user_warn() is similar, but uses SIGNAL to generate a warning for
# nonexistent users that can be displayed with SHOW WARNINGS;

# Run this script with mysql -f to continue even if errors occur.
# This enables the effect of DROP USER to be compared with the
# effect of drop_user().

# Requires the exec_stmt() procedure.

DROP PROCEDURE IF EXISTS drop_user;
delimiter $$
#@ _DEFINITION_1_
CREATE PROCEDURE drop_user(user TEXT, host TEXT)
BEGIN
  DECLARE account TEXT;
  DECLARE CONTINUE HANDLER FOR 1396
    SELECT CONCAT('Unknown user: ', account) AS Message;
  SET account = CONCAT(QUOTE(user),'@',QUOTE(host));
  CALL exec_stmt(CONCAT('DROP USER ',account));
END;
#@ _DEFINITION_1_
$$
delimiter ;

# Note: Use an account name that is unlikely to exist. In the unlikely
# event that it does exist, no error occurs for the DROP USER statement.
# In that case, just run the script again because the account will no
# longer exist after the first invocation ends.

# An error should occur here
DROP USER 'bad-user'@'localhost';

# An error should occur and be ignored with a message here
CALL drop_user('bad-user','localhost');

# Alternate implementation that uses an empty handler block (ignore the
# error completely, not even displaying a message).

DROP PROCEDURE IF EXISTS drop_user;
delimiter $$
CREATE PROCEDURE drop_user(user TEXT, host TEXT)
BEGIN
  DECLARE account TEXT;
#@ _EMPTY_HANDLER_
  DECLARE CONTINUE HANDLER FOR 1396 BEGIN END;
#@ _EMPTY_HANDLER_
  SET account = CONCAT(QUOTE(user),'@',QUOTE(host));
  CALL exec_stmt(CONCAT('DROP USER ',account));
END;
$$
delimiter ;

# An error should occur and be ignored silently here
CALL drop_user('bad-user','localhost');

# Reimplementation that generates a warning

DROP PROCEDURE IF EXISTS drop_user_warn;
delimiter $$
#@ _DEFINITION_2_
CREATE PROCEDURE drop_user_warn(user TEXT, host TEXT)
BEGIN
  DECLARE account TEXT;
  DECLARE CONTINUE HANDLER FOR 1396
  BEGIN
    DECLARE msg TEXT;
    SET msg = CONCAT('Unknown user: ', account);
    SIGNAL SQLSTATE '01000' SET MYSQL_ERRNO = 1642, MESSAGE_TEXT = msg;
  END;
  SET account = CONCAT(QUOTE(user),'@',QUOTE(host));
  CALL exec_stmt(CONCAT('DROP USER ',account));
END;
#@ _DEFINITION_2_
$$
delimiter ;

# A warning should be generated here
CALL drop_user_warn('bad-user','localhost');
SHOW WARNINGS;
