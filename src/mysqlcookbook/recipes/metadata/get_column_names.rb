#!/usr/bin/ruby
# get_column_names.rb: wrapper to demonstrate get_column_names()
# utility routine

# Assumes that you've created the "image" table!

require "Cookbook"
require "Cookbook_Utils"

db_name = "cookbook"
tbl_name = "image"

begin
  client = Cookbook.connect
rescue Mysql2::Error => e
  puts "Could not connect to server"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
end

puts "Using get_column_names()"
puts "Columns in #{db_name}.#{tbl_name} table:"
names = get_column_names(client, db_name, tbl_name)
puts names.join(", ")

puts "Construct statement to select all but data column:"
#@ _ALL_BUT_
names = get_column_names(client, db_name, tbl_name).reject { |name|
          name == "data"
        }
names.collect! { |name| quote_identifier(name) }
db_name = quote_identifier(db_name)
tbl_name = quote_identifier(tbl_name)
stmt = "SELECT " + names.join(",") + " FROM #{db_name}.#{tbl_name}"
#@ _ALL_BUT_
puts stmt

client.close
