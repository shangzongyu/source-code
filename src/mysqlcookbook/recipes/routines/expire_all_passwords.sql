# expire_all_passwords.sql

# expire_all_passwords() issues an ALTER USER .. PASSWORD EXPIRE statement
# for every nonanonymous account. (This assumes MySQL 5.6.7 or later.)

# Requires the exec_stmt() procedure.

# You could cheat and do this, but the procedure avoids modifying the
# grant tables directly:
# UPDATE mysql.user SET password_expired = 'Y';
# FLUSH PRIVILEGES;

DROP PROCEDURE IF EXISTS expire_all_passwords;
delimiter $$
#@ _DEFINITION_
CREATE PROCEDURE expire_all_passwords()
BEGIN
  DECLARE done BOOLEAN DEFAULT FALSE;
  DECLARE account TEXT;
  DECLARE cur CURSOR FOR
    SELECT CONCAT(QUOTE(User),'@',QUOTE(Host)) AS account
    FROM mysql.user WHERE User <> '';
  DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;

  OPEN cur;
  expire_loop: LOOP
    FETCH cur INTO account;
    IF done THEN
      LEAVE expire_loop;
    END IF;
    CALL exec_stmt(CONCAT('ALTER USER ',account,' PASSWORD EXPIRE'));
  END LOOP;
  CLOSE cur;
END;
#@ _DEFINITION_
$$
delimiter ;

CALL expire_all_passwords();
