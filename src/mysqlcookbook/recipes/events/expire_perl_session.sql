# expire_perl_session.sql

# Expire rows from the perl_session table discussed in the sessions chapter.

DROP EVENT IF EXISTS expire_perl_session;
#@ _DEFINE_
CREATE EVENT expire_perl_session
  ON SCHEDULE EVERY 4 HOUR
  DO DELETE FROM perl_session WHERE update_time < NOW() - INTERVAL 4 HOUR;
#@ _DEFINE_
