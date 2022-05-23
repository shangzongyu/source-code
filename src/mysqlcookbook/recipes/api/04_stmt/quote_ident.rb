#!/usr/bin/ruby
# quote_ident.rb: demonstrate identifier quoting in Ruby

require "Cookbook"
require "Cookbook_Utils" # location of quote_identifier()

begin
  client = Cookbook.connect
rescue Mysql2::Error => e
  puts "Cannot connect to server"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
  exit(1)
end

# This example uses database, table, and column names as identifiers,
# and quotes them as such

db_name = "some db"
tbl_name = "some`table"
col_name = "some column`name"

stmt = sprintf("SELECT %s FROM %s.%s",
                quote_identifier(col_name),
                quote_identifier(db_name),
                quote_identifier(tbl_name))
# Show resulting statement
puts stmt

# This example uses database and table names as data values,
# and quotes them as such

db_name = "cookbook"
tbl_name = "profile"

#@ _IDENT_AS_DATA_
sth = client.prepare("SELECT COLUMN_NAME
                        FROM INFORMATION_SCHEMA.COLUMNS
                        WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?")
names = sth.execute(db_name, tbl_name)
#@ _IDENT_AS_DATA_
names.each do |name|
   puts name
end

client.close
