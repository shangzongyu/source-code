# poll_vote.sql

DROP TABLE IF EXISTS poll_vote;
#@ _CREATE_TABLE_
CREATE TABLE poll_vote
(
  poll_id      INT UNSIGNED NOT NULL AUTO_INCREMENT,
  candidate_id INT UNSIGNED,
  vote_count   INT UNSIGNED,
  PRIMARY KEY (poll_id, candidate_id)
);
#@ _CREATE_TABLE_

SELECT * FROM poll_vote;
