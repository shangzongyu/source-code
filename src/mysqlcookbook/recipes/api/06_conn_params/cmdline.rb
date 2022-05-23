#!/usr/bin/ruby
# cmdline.rb: demonstrate command-line option parsing in Ruby

require "getoptlong"
require "mysql2"

# connection parameters - all missing (nil) by default
host_name = nil
password = nil
user_name = nil

opts = GetoptLong.new(
  [ "--host",     "-h", GetoptLong::REQUIRED_ARGUMENT ],
  [ "--password", "-p", GetoptLong::REQUIRED_ARGUMENT ],
  [ "--user",     "-u", GetoptLong::REQUIRED_ARGUMENT ]
)

# iterate through options, extracting whatever values are present;
# opt is the long-format option, arg is its value
opts.each do |opt, arg|
  case opt
  when "--host"
    host_name = arg
  when "--password"
    password = arg
  when "--user"
    user_name = arg
  end
end

# any nonoption arguments remain in ARGV
# and can be processed here as necessary

# connect to server
begin
  if !host_name.nil?
    client = Mysql2::Client.new(:host => host_name, 
                                :username => user_name, 
                                :password => password,
                                :databse => "cookbook")
  else
    client = Mysql2::Client.new(:username => user_name, 
                                :password => password,
                                :databse => "cookbook")
  end
  puts "Connected"
rescue Mysql2::Error => e
  puts "Cannot connect to server"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
  exit(1)
end

client.close
puts "Disconnected"
