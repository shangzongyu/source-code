# booksales.sql

# Increment sales for a book (using UPDATE).
# Then retrieve new value.
# (without LAST_INSERT_ID()

# This method requires that a row for the book exist already.
TRUNCATE TABLE booksales;
#@ _INSERT_0_
INSERT INTO booksales (title,copies) VALUES('The Greater Trumps',0);
#@ _INSERT_0_

#@ _UPDATE_1_
UPDATE booksales SET copies = copies+1 WHERE title = 'The Greater Trumps';
#@ _UPDATE_1_
#@ _SELECT_1_
SELECT copies FROM booksales WHERE title = 'The Greater Trumps';
#@ _SELECT_1_

# Do same using LAST_INSERT_ID()

#@ _UPDATE_2_
UPDATE booksales SET copies = LAST_INSERT_ID(copies+1)
WHERE title = 'The Greater Trumps';
#@ _UPDATE_2_
#@ _SELECT_2_
SELECT LAST_INSERT_ID();
#@ _SELECT_2_

# Increment sales by a dozen copies rather than by 1 copy

#@ _UPDATE_3_
UPDATE booksales SET copies = LAST_INSERT_ID(copies+12)
WHERE title = 'The Greater Trumps';
#@ _UPDATE_3_
#@ _SELECT_3_
SELECT LAST_INSERT_ID();
#@ _SELECT_3_

# Increment sales for a book (using INSERT ... ON DUPLICATE KEY UPDATE).
# Then retrieve new value.
# (without LAST_INSERT_ID()

# This method does not require that a row for the book exist already.
TRUNCATE TABLE booksales;

#@ _INSERT_1_
INSERT INTO booksales (title,copies)
VALUES('The Greater Trumps',1)
ON DUPLICATE KEY UPDATE copies = copies+1;
#@ _INSERT_1_
SELECT copies FROM booksales WHERE title = 'The Greater Trumps';

# Do same using LAST_INSERT_ID()

#@ _INSERT_2_
INSERT INTO booksales (title,copies)
VALUES('The Greater Trumps',LAST_INSERT_ID(1))
ON DUPLICATE KEY UPDATE copies = LAST_INSERT_ID(copies+1);
#@ _INSERT_2_
SELECT LAST_INSERT_ID();

# Increment sales by a dozen copies rather than by 1 copy

#@ _INSERT_3_
INSERT INTO booksales (title,copies)
VALUES('The Greater Trumps',LAST_INSERT_ID(12))
ON DUPLICATE KEY UPDATE copies = LAST_INSERT_ID(copies+12);
#@ _INSERT_3_
SELECT LAST_INSERT_ID();
