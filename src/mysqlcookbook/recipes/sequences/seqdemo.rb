#!/usr/bin/ruby
# seqdiag.rb: test AUTO_INCREMENT operations

require "Cookbook"

begin
  client = Cookbook.connect
rescue Mysql2::Error => e
  puts "Cannot connect to server"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
  exit(1)
end

#@ _CLIENT_SIDE_FAILURE_
client.query("SET @x = LAST_INSERT_ID(48)")
seq = client.last_id
#@ _CLIENT_SIDE_FAILURE_
puts "seq after SET via insert_id: #{seq}"
#@ _CLIENT_SIDE_SUCCESS_
seq = client.query("SELECT LAST_INSERT_ID()").first.values[0]
#@ _CLIENT_SIDE_SUCCESS_
puts "seq after SET via LAST_INSERT_ID(): #{seq}"

client.close
