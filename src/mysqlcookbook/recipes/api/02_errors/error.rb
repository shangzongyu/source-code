#!/usr/bin/ruby
# error.rb: demonstrate MySQL error handling

require "mysql2"

#@ _FRAG_
begin
  client = Mysql2::Client.new(:host => "localhost",
                              :username => "baduser",
                              :password => "badpass",
                              :database => "cookbook")
  puts "Connected"
rescue Mysql2::Error => e
  puts "Cannot connect to server"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
  puts "Error SQLSTATE: #{e.sql_state}"
  exit(1)
end
#@ _FRAG_
client.close()
puts "Disconnected"
