# enable_failed_login_attempts.sql

# enable_failed_login_attempts() takes an account given as a user name and host name and
# enables FAILED_LOGIN_ATTEMPTS option if the ALTER USER ... FAILED_LOGIN_ATTEMPTSstatement is available (MySQL 8.0.19)
# and user is not anonymous. This is a simple example of adaptive SQL.

# Requires the exec_stmt() procedure and server_version() function.

DROP PROCEDURE IF EXISTS enable_failed_login_attempts;
delimiter $$
#@ _DEFINITION_
CREATE PROCEDURE enable_failed_login_attempts(user TEXT, host TEXT, failed_atempts INT)
BEGIN
  DECLARE account TEXT;
  SET account = CONCAT(QUOTE(user),'@',QUOTE(host));
  IF server_version() >= 80019 AND user <> '' THEN
    CALL exec_stmt(CONCAT('ALTER USER ',account,' FAILED_LOGIN_ATTEMPTS ', failed_atempts));
  END IF;
END;
#@ _DEFINITION_
$$
delimiter ;

CALL enable_failed_login_attempts('user7','localhost', 3);
