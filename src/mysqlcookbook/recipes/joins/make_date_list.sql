# make_date_list.sql: create a table with an entry for every date in
# a given date range.  The table can be used in a LEFT JOIN when
# producing a summary, to ensure that every date appears in the
# summary, regardless of whether the data to be summarized actually
# contains any values for a given day.

DROP PROCEDURE IF EXISTS make_date_list;
delimiter $$
#@ _DEFINITION_
CREATE PROCEDURE make_date_list(db_name TEXT, tbl_name TEXT, col_name TEXT,
                                min_date DATE, max_date DATE)
BEGIN
  DECLARE i, days INT;
  SET i = 0, days = DATEDIFF(max_date,min_date)+1;

  # Make identifiers safe for insertion into SQL statements. Use db_name
  # and tbl_name to create qualified table name.
  SET tbl_name = CONCAT(quote_identifier(db_name),'.',
                        quote_identifier(tbl_name));
  SET col_name = quote_identifier(col_name);
  CALL exec_stmt(CONCAT('DROP TABLE IF EXISTS ',tbl_name));
  CALL exec_stmt(CONCAT('CREATE TABLE ',tbl_name,'(',
                        col_name,' DATE NOT NULL, PRIMARY KEY(',
                        col_name,'))'));
  WHILE i < days DO
    CALL exec_stmt(CONCAT('INSERT INTO ',tbl_name,'(',col_name,') VALUES(',
                          QUOTE(min_date),' + INTERVAL ',i,' DAY)'));
    SET i = i + 1;
  END WHILE;
END;
#@ _DEFINITION_
$$

delimiter ;
#@ _USE_
CALL make_date_list('cookbook', 'dates', 'd', '2014-07-26', '2014-08-02');
#@ _USE_
