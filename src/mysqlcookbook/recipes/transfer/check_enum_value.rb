#!/usr/bin/ruby
# check_enum_value.rb: Wrapper to demonstrate check_enum_value()
# utility function that determines whether a value is a member of
# a given ENUM column.

# Usage: check_enum_value.rb db_name tbl_name col_name test_value

require "Cookbook"
require "Cookbook_Utils"

if ARGV.length != 4
  puts "Usage: check_enum_value.rb db_name tbl_name col_name test_val"
  exit(1)
end

db_name = ARGV[0]
tbl_name = ARGV[1]
col_name = ARGV[2]
val = ARGV[3]

begin
  client = Cookbook.connect
rescue Mysql2::Error => e
  puts "Could not connect to server"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
end

valid = check_enum_value(client, db_name, tbl_name, col_name, val)

puts "#{val} " +
     (valid ? "is" : "is not") +
     " a member of #{tbl_name}.#{col_name}"

client.close
