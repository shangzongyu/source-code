#!/usr/bin/ruby
# connect.rb: connect to the MySQL server

require "mysql2"

begin
  client = Mysql2::Client.new(:host => "localhost", 
                              :username => "cbuser",
                              :password => "cbpass",
                              :database => "cookbook")
  puts "Connected"
rescue => e
  puts "Cannot connect to server"
  puts e.backtrace
  exit(1)
ensure
  client.close()
  puts "Disconnected"
end
