#!/usr/bin/ruby
# high_level.rb: demonstrate higher-level retrieval methods in Ruby
# (without placeholders)

require "Cookbook"

begin
  client = Cookbook.connect
rescue Mysql2::Error => e
  puts "Cannot connect to server"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
  exit(1)
end

puts "Fetch all rows"
begin
#@ _SELECT_ALL_NO_ITERATOR_
  rows = client.query( "SELECT id, name, cats FROM profile")
#@ _SELECT_ALL_NO_ITERATOR_
  rows.each do |row|
    printf "id: %s, name: %s, cats: %s\n",
           row["id"], row["name"], row["cats"]
  end
rescue Mysql2::Error => e
  puts "Oops, the statement failed"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
end

puts "Fetch all rows, applying iterator directly to select_all"
begin
#@ _SELECT_ALL_ITERATOR_
  client.query("SELECT id, name, cats FROM profile").each do |row|
    printf "id: %s, name: %s, cats: %s\n",
           row["id"], row["name"], row["cats"]
  end
#@ _SELECT_ALL_ITERATOR_
rescue Mysql2::Error => e
  puts "Oops, the statement failed"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
end

client.close
