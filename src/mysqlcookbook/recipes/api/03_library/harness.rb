#!/usr/bin/ruby
# harness.rb: test harness for Cookbook.rb library

require "Cookbook"

begin
  client = Cookbook.connect
  print "Connected\n"
rescue Mysql2::Error => e
  puts "Cannot connect to server"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
  exit(1)
ensure
  client.close
  print "Disconnected\n"
end
