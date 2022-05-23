# al_winner.sql

# Table to hold American League winners of 15 or more games in 2001.

DROP TABLE IF EXISTS al_winner;
#@ _CREATE_TABLE_
CREATE TABLE al_winner
(
  name CHAR(30),
  wins INT,
  PRIMARY KEY(name)
);
#@ _CREATE_TABLE_

LOAD DATA LOCAL INFILE 'al_winner-2001.txt' INTO TABLE al_winner;

SELECT * FROM al_winner;

SET @n = 0;
SET @val = 0;
SELECT @n:=IF(@val=wins,@n,@n+1) AS al_ank, name, @val:=wins AS wins
FROM al_winner ORDER BY wins DESC, name;
