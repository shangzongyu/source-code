#!/usr/bin/ruby
# option_file.rb: demonstrate DSN options for reading MySQL option files

require "mysql2"

begin
#@ _FRAG1_
  # look in user-specific option file owned by the current user
  client = Mysql2::Client.new(:default_file => "#{ENV['HOME']}/.my.cnf",
                              :database => "cookbook")
#@ _FRAG1_
  puts "Connected"
rescue Mysql2::Error => e
  puts "Cannot connect to server"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
else
  client.close()
  puts "Disconnected"
end

begin
#@ _FRAG2_
  # look in standard option files; use [cookbook] and [client] groups
  client = Mysql2::Client.new(:default_group => "cookbook",
                              :database => "cookbook")
#@ _FRAG2_
  puts "Connected"
rescue Mysql2::Error => e
  puts "Cannot connect to server"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
else
  client.close()
  puts "Disconnected"
end
