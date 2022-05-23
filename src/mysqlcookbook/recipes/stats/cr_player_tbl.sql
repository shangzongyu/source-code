# cr_player_tbl.sql

DROP TABLE IF EXISTS player;
CREATE TABLE player
(
  id    INT NOT NULL AUTO_INCREMENT,
  name  CHAR(10),
  PRIMARY KEY (id)
)
;

INSERT INTO player (name) VALUES('Francine');
INSERT INTO player (name) VALUES('Geoffrey');
INSERT INTO player (name) VALUES('Maxwell');
INSERT INTO player (name) VALUES('Imogene');

SELECT id FROM player ORDER BY RAND()
;
