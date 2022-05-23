# deck.sql

# Create a deck table to contain rows for a deck of cards and show various
# randomization operations

DROP TABLE IF EXISTS deck;
CREATE TABLE deck
(
  face  ENUM('A', 'K', 'Q', 'J', '10', '9', '8',
              '7', '6', '5', '4', '3', '2'),
  suit  ENUM('hearts', 'diamonds', 'clubs', 'spades')
);

INSERT INTO deck (face,suit) VALUES('A','hearts');
INSERT INTO deck (face,suit) VALUES('A','diamonds');
INSERT INTO deck (face,suit) VALUES('A','clubs');
INSERT INTO deck (face,suit) VALUES('A','spades');
INSERT INTO deck (face,suit) VALUES('K','hearts');
INSERT INTO deck (face,suit) VALUES('K','diamonds');
INSERT INTO deck (face,suit) VALUES('K','clubs');
INSERT INTO deck (face,suit) VALUES('K','spades');
INSERT INTO deck (face,suit) VALUES('Q','hearts');
INSERT INTO deck (face,suit) VALUES('Q','diamonds');
INSERT INTO deck (face,suit) VALUES('Q','clubs');
INSERT INTO deck (face,suit) VALUES('Q','spades');
INSERT INTO deck (face,suit) VALUES('J','hearts');
INSERT INTO deck (face,suit) VALUES('J','diamonds');
INSERT INTO deck (face,suit) VALUES('J','clubs');
INSERT INTO deck (face,suit) VALUES('J','spades');
INSERT INTO deck (face,suit) VALUES('10','hearts');
INSERT INTO deck (face,suit) VALUES('10','diamonds');
INSERT INTO deck (face,suit) VALUES('10','clubs');
INSERT INTO deck (face,suit) VALUES('10','spades');
INSERT INTO deck (face,suit) VALUES('9','hearts');
INSERT INTO deck (face,suit) VALUES('9','diamonds');
INSERT INTO deck (face,suit) VALUES('9','clubs');
INSERT INTO deck (face,suit) VALUES('9','spades');
INSERT INTO deck (face,suit) VALUES('8','hearts');
INSERT INTO deck (face,suit) VALUES('8','diamonds');
INSERT INTO deck (face,suit) VALUES('8','clubs');
INSERT INTO deck (face,suit) VALUES('8','spades');
INSERT INTO deck (face,suit) VALUES('7','hearts');
INSERT INTO deck (face,suit) VALUES('7','diamonds');
INSERT INTO deck (face,suit) VALUES('7','clubs');
INSERT INTO deck (face,suit) VALUES('7','spades');
INSERT INTO deck (face,suit) VALUES('6','hearts');
INSERT INTO deck (face,suit) VALUES('6','diamonds');
INSERT INTO deck (face,suit) VALUES('6','clubs');
INSERT INTO deck (face,suit) VALUES('6','spades');
INSERT INTO deck (face,suit) VALUES('5','hearts');
INSERT INTO deck (face,suit) VALUES('5','diamonds');
INSERT INTO deck (face,suit) VALUES('5','clubs');
INSERT INTO deck (face,suit) VALUES('5','spades');
INSERT INTO deck (face,suit) VALUES('4','hearts');
INSERT INTO deck (face,suit) VALUES('4','diamonds');
INSERT INTO deck (face,suit) VALUES('4','clubs');
INSERT INTO deck (face,suit) VALUES('4','spades');
INSERT INTO deck (face,suit) VALUES('3','hearts');
INSERT INTO deck (face,suit) VALUES('3','diamonds');
INSERT INTO deck (face,suit) VALUES('3','clubs');
INSERT INTO deck (face,suit) VALUES('3','spades');
INSERT INTO deck (face,suit) VALUES('2','hearts');
INSERT INTO deck (face,suit) VALUES('2','diamonds');
INSERT INTO deck (face,suit) VALUES('2','clubs');
INSERT INTO deck (face,suit) VALUES('2','spades');

# "Shuffle" cards

#@ _SHUFFLE_1_
SELECT face, suit FROM deck ORDER BY RAND();
#@ _SHUFFLE_1_

# In MySQL < 3.23, ORDER BY cannot contain expressions.  Create an
# extra output column containing random numbers, alias it, and refer
# to the alias in the ORDER BY clause.

#@ _SHUFFLE_2_
SELECT face, suit, face*0+RAND() AS rand_num FROM deck ORDER BY rand_num;
#@ _SHUFFLE_2_

# The following method won't work for MySQL < 3.23 because the optimizer
# assumes incorrectly that the rand_val column value is constant for
# each row and optimized the ORDER BY clause out of the query.

#@ _SHUFFLE_WRONG_
SELECT face, suit, RAND() AS rand_num FROM deck ORDER BY rand_num;
#@ _SHUFFLE_WRONG_
