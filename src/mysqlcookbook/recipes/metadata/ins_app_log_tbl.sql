# ins_app_log_tbl.sql

# insert a record into the app_log table

#@ _FRAG_
INSERT INTO app_log
  SET user = SUBSTRING_INDEX(USER(),'@',1),
      host = SUBSTRING_INDEX(USER(),'@',-1);
#@ _FRAG_
