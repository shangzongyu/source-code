#!/usr/bin/ruby
# booksales.rb: show how to use LAST_INSERT_ID(expr)

require "Cookbook"

begin
  client = Cookbook.connect
rescue Mysql2::Error => e
  puts "Cannot connect to server"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
  exit(1)
end

# Show how to generate an AUTO_INCREMENT value and retrieve it using
# the database handle.

#@ _USE_DBH_
client.query("INSERT INTO booksales (title,copies)
        VALUES('The Greater Trumps',LAST_INSERT_ID(1))
        ON DUPLICATE KEY UPDATE copies = LAST_INSERT_ID(copies+1)")
count = client.last_id
#@ _USE_DBH_
puts "count: #{count}"

client.close
