# Execute using mysql -f
# Script to create a bunch of accounts that are bad in various ways and
# should be upgraded, and then upgrade them.

# So INSERT will insert rows even though BLOB columns aren't specified
# and have no defaults.

SET sql_mode='';

# Q: Should I also set up something for sha256_password?

SET old_passwords=0;
DELETE FROM mysql.user WHERE User LIKE 'user%';
FLUSH PRIVILEGES;
INSERT INTO mysql.user (Host, User, Password, Plugin)
VALUES
 ('localhost','user1',PASSWORD('mypass'),'mysql_native_password')
,('localhost','user2','','')
,('localhost','user3','','mysql_old_password')
,('localhost','user4',OLD_PASSWORD('mypass'),'')
,('localhost','user5',OLD_PASSWORD('mypass'),'mysql_old_password')
,('localhost','user6','','mysql_native_password')
,('localhost','user7',PASSWORD('mypass'),'')
;

FLUSH PRIVILEGES;
SELECT User, plugin, Password FROM mysql.user
WHERE User like 'user%' AND Host = 'localhost'
ORDER BY User;

# Find insecure accounts, method 1
#@ _FIND_INSECURE_1_
SELECT User, Host, plugin, Password FROM mysql.user
WHERE (plugin = 'mysql_native_password' AND Password = '')
      OR plugin IN ('','mysql_old_password');
#@ _FIND_INSECURE_1_

# Need FLUSH PRIVILEGES after any UPDATE

# User 2: Specify _native_ plugin, assign password
#@ _UPGRADE_USER2_
UPDATE mysql.user
SET plugin = 'mysql_native_password', Password = PASSWORD('mypass')
WHERE User = 'user2' AND Host = 'localhost';
FLUSH PRIVILEGES;
#@ _UPGRADE_USER2_

# User 3: Change to _native_ plugin, assign password
#@ _UPGRADE_USER3_
UPDATE mysql.user
SET plugin = 'mysql_native_password', Password = PASSWORD('mypass')
WHERE User = 'user3' AND Host = 'localhost';
FLUSH PRIVILEGES;
#@ _UPGRADE_USER3_

# User 4: Specify _native_ plugin, upgrade password hash format
#@ _UPGRADE_USER4_
UPDATE mysql.user
SET plugin = 'mysql_native_password', Password = PASSWORD('mypass')
WHERE User = 'user4' AND Host = 'localhost';
FLUSH PRIVILEGES;
#@ _UPGRADE_USER4_

# User 5: Change to _native_ plugin, upgrade password hash format
#@ _UPGRADE_USER5_
UPDATE mysql.user
SET plugin = 'mysql_native_password', Password = PASSWORD('mypass')
WHERE User = 'user5' AND Host = 'localhost';
FLUSH PRIVILEGES;
#@ _UPGRADE_USER5_

# User 6: Assign password
#@ _UPGRADE_USER6_
SET PASSWORD FOR 'user6'@'localhost' = PASSWORD('mypass');
#@ _UPGRADE_USER6_

# User 7: Specify _native_ plugin
#@ _UPGRADE_USER7_
UPDATE mysql.user
SET plugin = 'mysql_native_password'
WHERE User = 'user7' AND Host = 'localhost';
FLUSH PRIVILEGES;
#@ _UPGRADE_USER7_

SELECT User, plugin, Password FROM mysql.user
WHERE User like 'user%' AND Host = 'localhost'
ORDER BY User;

# Find insecure accounts again (should be empty)
SELECT User, Host, plugin, Password FROM mysql.user
WHERE plugin IN ('','mysql_old_password')
      OR (plugin IN ('mysql_old_password','mysql_native_password')
          AND Password = '');
