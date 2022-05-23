#!/usr/bin/ruby
# get_connection_meta.rb: get connection metadata

require "Cookbook"

begin
  client = Cookbook.connect
rescue Mysql2::Error => e
  puts "Could not connect to server"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
end

#@ _CURRENT_DATABASE_
db = client.query("SELECT DATABASE()").first.values[0]
puts "Default database: " + (db.nil? ? "(no database selected)" : db)
#@ _CURRENT_DATABASE_

client.close
