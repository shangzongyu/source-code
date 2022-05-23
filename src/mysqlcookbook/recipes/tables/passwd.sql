# passwd.sql

# create table for loading the /etc/passwd file (except the password
# and directory fields)

DROP TABLE IF EXISTS passwd;
#@ _CREATE_TABLE_
CREATE TABLE passwd
(
  account   CHAR(8),  # login name
  uid       INT,      # user ID
  gid       INT,      # group ID
  gecos     CHAR(60), # name, phone, office, etc.
  shell     CHAR(60),  # command interpreter
  PRIMARY KEY(account)
);
#@ _CREATE_TABLE_
