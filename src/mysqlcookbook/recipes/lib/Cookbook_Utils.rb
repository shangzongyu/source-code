# Cookbook_Utils.rb: MySQL Cookbook utilities

# Quote an identifier by doubling internal backticks and adding
# a backtick at the beginning and end.

#@ _QUOTE_IDENTIFIER_
def quote_identifier(ident)
  return "`" + ident.gsub(/`/, "``") + "`"
end
#@ _QUOTE_IDENTIFIER_

# Given database and table names, return an array containing the
# of the table's columns, in table definition order.

#@ _GET_COLUMN_NAMES_
def get_column_names(client, db_name, tbl_name)
  stmt = "SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS
          WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?
          ORDER BY ORDINAL_POSITION"
  sth = client.prepare(stmt) 
  res = sth.execute(db_name, tbl_name)
  return res.collect { |row| row.values[0] }
end
#@ _GET_COLUMN_NAMES_

# Given database and table names, return information about the table columns.
# Return value is a hash keyed by column name. Each array element is
# a hash keyed by name of column in the INFORMATION_SCHEMA.COLUMNS table.

#@ _GET_COLUMN_INFO_
def get_column_info(client, db_name, tbl_name)
  col_info = {}
  stmt = "SELECT * FROM INFORMATION_SCHEMA.COLUMNS
          WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?"
  sth = client.prepare(stmt)
  res = sth.execute(db_name, tbl_name)
  res.each do |row|
    col_info[row["COLUMN_NAME"]] = row
  end
  return col_info
end
#@ _GET_COLUMN_INFO_

# get_enumorset_info() - get metadata for an ENUM or SET column.
# Take a database connection and database, table, and column names.
# Return a hash keyed by "name", "type", "values", "nullable",
# and "default". Return nil if no info available.

#@ _GET_ENUMORSET_INFO_
def get_enumorset_info(client, db_name, tbl_name, col_name)
  sth = client.prepare(
          "SELECT COLUMN_NAME, COLUMN_TYPE, IS_NULLABLE, COLUMN_DEFAULT
           FROM INFORMATION_SCHEMA.COLUMNS
           WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ? AND COLUMN_NAME = ?")
  res = sth.execute(db_name, tbl_name, col_name)
  return nil if res.count == 0  # no such column
  row = res.first
  info = {}
  info["name"] = row.values[0]
  return nil unless row.values[1] =~ /^(ENUM|SET)\((.*)\)$/i # not ENUM or SET
  info["type"] = $1
  # split value list on commas, trim quotes from end of each word
  info["values"] = $2.split(",").collect { |val| val.sub(/^'(.*)'$/, "\\1") }
  # determine whether column can contain NULL values
  info["nullable"] = (row.values[2].upcase == "YES")
  # get default value (nil represents NULL)
  info["default"] = row.values[3]
  return info
end
#@ _GET_ENUMORSET_INFO_

#@ _CHECK_ENUM_VALUE_
def check_enum_value(client, db_name, tbl_name, col_name, val)
  valid = false
  info = get_enumorset_info(client, db_name, tbl_name, col_name)
  if !info.nil? && info["type"].upcase == "ENUM"
    # use case-insensitive comparison because default collation
    # (latin1_swedish_ci) is case-insensitive (adjust if you use
    # a different collation)
    val = val.upcase
    info["values"].each do |v|
      if val == v.upcase
        valid = true
        break
      end
    end
  end
  return valid
end
#@ _CHECK_ENUM_VALUE_
