# standings1.sql

# Team standings table for single group of team records

DROP TABLE IF EXISTS standings1;
CREATE TABLE standings1
(
  team  CHAR(20), # team name
  wins  INT,      # number of wins
  losses  INT,     # number of losses
  PRIMARY KEY(team)
);

# Load Northern League final 1902 standings into the table

INSERT INTO standings1 (team, wins, losses) VALUES ('Winnipeg',37,20);
INSERT INTO standings1 (team, wins, losses) VALUES ('Crookston',31,25);
INSERT INTO standings1 (team, wins, losses) VALUES ('Fargo',30,26);
INSERT INTO standings1 (team, wins, losses) VALUES ('Grand Forks',28,26);
INSERT INTO standings1 (team, wins, losses) VALUES ('Devils Lake',19,31);
INSERT INTO standings1 (team, wins, losses) VALUES ('Cavalier',15,32);

SELECT * FROM standings1;
