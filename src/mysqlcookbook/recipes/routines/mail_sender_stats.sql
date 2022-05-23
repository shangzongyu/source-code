# mail_sender_stats.sql

# Illustrate the use of OUT parameters for returning results from a
# procedure through user-defined variables.  Given a username,
# the procedure determines the number of messages sent by the user,
# and the total and average size of those messages in bytes.

DROP PROCEDURE IF EXISTS mail_sender_stats;
delimiter $$
#@ _DEFINITION_
CREATE PROCEDURE mail_sender_stats(IN user VARCHAR(8),
                                   OUT messages INT,
                                   OUT total_size INT,
                                   OUT avg_size INT)
BEGIN
  # Use IFNULL() to return 0 for SUM() and AVG() in case there are
  # no rows for the user (those functions return NULL in that case).
  SELECT COUNT(*), IFNULL(SUM(size),0), IFNULL(AVG(size),0)
  INTO messages, total_size, avg_size
  FROM mail WHERE srcuser = user;
END;
#@ _DEFINITION_
$$

delimiter ;
CALL mail_sender_stats('barb',@messages,@total_size,@avg_size);
SELECT 'barb', @messages, @total_size, @avg_size;
CALL mail_sender_stats('erasmus',@messages,@total_size,@avg_size);
SELECT 'erasmus', @messages, @total_size, @avg_size;
