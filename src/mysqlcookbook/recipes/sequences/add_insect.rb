#!/usr/bin/ruby
# add_insect.rb: demonstrate client-side insert_id attribute
# for getting the most recent AUTO_INCREMENT value.

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

#@ _INSERT_ID_
client.query("INSERT INTO insect (name,date,origin)
        VALUES('moth','2014-09-14','windowsill')")
seq = client.last_id
#@ _INSERT_ID_
puts "seq: #{seq}"

client.close
