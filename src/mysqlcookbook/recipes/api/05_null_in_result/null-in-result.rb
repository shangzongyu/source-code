#!/usr/bin/ruby
# null-in-result.rb: demonstrate NULL values in the result set
# processing in Ruby

require "Cookbook"

begin
  client = Cookbook.connect
rescue Mysql2::Error => e
  puts "Cannot connect to server"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
  exit(1)
end

begin
#@ _EACHLOOP_
  result = client.query("SELECT name, birth, foods FROM profile")
  result.each do |row|
    printf "name %s, birth: %s, foods: %s\n", 
           row["name"].nil? ? "NULL" : row["name"], 
           row["birth"].nil? ? "NULL" : row["birth"], 
           row["foods"].nil? ? "NULL" : row["foods"]
  end
#@ _EACHLOOP_
rescue Mysql2::Error => e
  puts "Oops, the statement failed"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
end

client.close
