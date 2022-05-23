# show_version.sql: Display MySQL version

DROP PROCEDURE IF EXISTS show_version;
#@ _DEFINITION_
CREATE PROCEDURE show_version()
SELECT VERSION() AS 'MySQL Version';
#@ _DEFINITION_

CALL show_version();
