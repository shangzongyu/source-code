# expire_rows.sql

# Given a database, table, and column name, and a time in seconds,
# expire_rows() expires rows from the table older than that many seconds.

# Requires the exec_stmt() procedure and quote_identifier() function.

# Note: CONCAT() implicitly converts maxsecs to string.

DROP PROCEDURE IF EXISTS expire_rows;
delimiter $$
#@ _DEFINE_
CREATE PROCEDURE expire_rows(db_name TEXT, tbl_name TEXT,
                             col_name TEXT, maxsecs BIGINT)
BEGIN
  # Construct this statement:
  # DELETE FROM `db_name`.`tbl_name`
  # WHERE `col_name` < NOW() - INTERVAL maxsecs SECOND
  CALL exec_stmt(CONCAT('DELETE FROM ',
                        quote_identifier(db_name),
                        '.',
                        quote_identifier(tbl_name),
                        ' WHERE ',
                        quote_identifier(col_name),
                        ' < NOW() - INTERVAL ', maxsecs,' SECOND'));
END;
#@ _DEFINE_
$$
delimiter ;

CALL expire_rows('cookbook','ruby_session','update_time',4*60*60);
