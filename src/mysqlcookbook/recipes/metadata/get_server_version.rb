#!/usr/bin/ruby
# get_server_version.rb: get server version string and number from server

# This script demonstrates how to get the string by issuing a
# SELECT VERSION() statement.

require "Cookbook"

# Return an array consisting of the server version number in both string
# and numeric forms.

def get_server_version(client)
  # fetch result into scalar string
  ver_str = client.query("SELECT VERSION()").first.values[0]
  major, minor, patch = ver_str.split(/\./)
  patch.sub!(/\D.*$/, "")  # strip nonnumeric suffix if present
  ver_num = major.to_i*10000 + minor.to_i*100 + patch.to_i
  [ver_str, ver_num]
end

begin
  client = Cookbook.connect
  # get server version string and number and print them
  ver_str, ver_num = get_server_version(client)
  puts "Version: #{ver_str} (#{ver_num})"
  client.close
rescue Mysql2::Error => e
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
end
