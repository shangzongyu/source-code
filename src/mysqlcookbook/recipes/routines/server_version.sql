# server_version.sql

# server_version() returns the MySQL server verion in numeric form.
# For example, if the version is "5.7.4-m14", it returns 50704.

DROP FUNCTION IF EXISTS server_version;
delimiter $$
#@ _DEFINITION_
CREATE FUNCTION server_version()
RETURNS INT READS SQL DATA
BEGIN
  DECLARE major, minor, patch INT DEFAULT 0;
  SET major = SUBSTRING_INDEX(VERSION(),'.',1);
  SET minor = SUBSTRING_INDEX(SUBSTRING_INDEX(VERSION(),'.',2),'.',-1);
  -- implicit conversion to integer here truncates nonnumeric suffix
  SET sql_mode = ''; -- suppress implicit truncation warning
  SET patch = SUBSTRING_INDEX(SUBSTRING_INDEX(VERSION(),'.',3),'.',-1);
  RETURN major * 10000 + minor * 100 + patch;
END;
#@ _DEFINITION_
$$
delimiter ;

SELECT server_version();
