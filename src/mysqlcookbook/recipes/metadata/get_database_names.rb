#!/usr/bin/ruby
# get_database_names.rb: list names of databases on server

require "Cookbook"

begin
  client = Cookbook.connect
rescue Mysql2::Error => e
  puts "Could not connect to server"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
end

puts "Get database names from INFORMATION_SCHEMA:"
stmt = "SELECT SCHEMA_NAME
        FROM INFORMATION_SCHEMA.SCHEMATA
        ORDER BY SCHEMA_NAME"
client.query(stmt).each do |row|
    puts row.values[0]
end

client.close
