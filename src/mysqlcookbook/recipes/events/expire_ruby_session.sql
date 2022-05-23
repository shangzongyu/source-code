# expire_ruby_session.sql

# Expire rows from the ruby_session table discussed in the sessions chapter.

DROP EVENT IF EXISTS expire_ruby_session;
#@ _DEFINE_
CREATE EVENT expire_ruby_session
  ON SCHEDULE EVERY 4 HOUR
  DO DELETE FROM ruby_session WHERE update_time < NOW() - INTERVAL 4 HOUR;
#@ _DEFINE_
