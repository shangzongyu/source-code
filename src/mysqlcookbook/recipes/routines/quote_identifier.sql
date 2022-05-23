# quote_identifier.sql

# quote_identifer() is like the built-in QUOTE() function
# but for identifiers. It returns the argument as a string
# safe for insertion as an identifier into SQL statements.
# The argument is returned enclosed within backticks and
# with internal backticks doubled.

DROP FUNCTION IF EXISTS quote_identifier;
#@ _DEFINITION_
CREATE FUNCTION quote_identifier(id TEXT)
RETURNS TEXT DETERMINISTIC
RETURN CONCAT('`',REPLACE(id,'`','``'),'`');
#@ _DEFINITION_

SELECT quote_identifier('abc');
SELECT quote_identifier('a`c');
