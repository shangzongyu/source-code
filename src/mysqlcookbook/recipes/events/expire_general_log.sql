# expire_general_log.sql

# Expire rows from the mysql.general_log table.

DROP EVENT IF EXISTS expire_general_log;
#@ _DEFINE_
CREATE EVENT expire_general_log
  ON SCHEDULE EVERY 1 WEEK
  DO DELETE FROM mysql.general_log
     WHERE event_time < NOW() - INTERVAL 1 WEEK;
#@ _DEFINE_
