#!/usr/bin/ruby
# get_column_info.rb: wrapper to demonstrate get_column_info()
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

puts "Using get_column_info()"
puts "Column information for #{db_name}.#{tbl_name} table:"
info = get_column_info(client, db_name, tbl_name)
info.each do |col_name, col_info|
  puts "  Column: #{col_name}"
  col_info.each do |col_val_key, col_val|
    puts "    #{col_val_key}: #{col_val}"
  end
end

client.close
