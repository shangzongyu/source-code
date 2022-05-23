# standings2.sql

# Team standings table for multiple groups of team records

DROP TABLE IF EXISTS standings2;
CREATE TABLE standings2
(
  id        INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
  half      INT,      # which half of season
  division  CHAR(10), # league division
  team      CHAR(20), # team name
  wins      INT,      # number of wins
  losses    INT       # number of losses
);

# Load Northern League final 1997 standings into the table.
# The standings are per-half season and per division (Easter, Western),
# thus there are four groups of standings

INSERT INTO standings2 (half, division, team, wins, losses)
  VALUES (1,'Eastern','St. Paul',24,18);
INSERT INTO standings2 (half, division, team, wins, losses)
  VALUES (1,'Eastern','Thunder Bay',18,24);
INSERT INTO standings2 (half, division, team, wins, losses)
  VALUES (1,'Eastern','Duluth-Superior',17,24);
INSERT INTO standings2 (half, division, team, wins, losses)
  VALUES (1,'Eastern','Madison',15,27);
INSERT INTO standings2 (half, division, team, wins, losses)
  VALUES (1,'Western','Winnipeg',29,12);
INSERT INTO standings2 (half, division, team, wins, losses)
  VALUES (1,'Western','Sioux City',28,14);
INSERT INTO standings2 (half, division, team, wins, losses)
  VALUES (1,'Western','Fargo-Moorhead',21,21);
INSERT INTO standings2 (half, division, team, wins, losses)
  VALUES (1,'Western','Sioux Falls',15,27);
INSERT INTO standings2 (half, division, team, wins, losses)
  VALUES (2,'Eastern','Duluth-Superior',22,20);
INSERT INTO standings2 (half, division, team, wins, losses)
  VALUES (2,'Eastern','St. Paul',21,21);
INSERT INTO standings2 (half, division, team, wins, losses)
  VALUES (2,'Eastern','Madison',19,23);
INSERT INTO standings2 (half, division, team, wins, losses)
  VALUES (2,'Eastern','Thunder Bay',18,24);
INSERT INTO standings2 (half, division, team, wins, losses)
  VALUES (2,'Western','Fargo-Moorhead',26,16);
INSERT INTO standings2 (half, division, team, wins, losses)
  VALUES (2,'Western','Winnipeg',24,18);
INSERT INTO standings2 (half, division, team, wins, losses)
  VALUES (2,'Western','Sioux City',22,20);
INSERT INTO standings2 (half, division, team, wins, losses)
  VALUES (2,'Western','Sioux Falls',16,26);

SELECT * FROM standings2;
