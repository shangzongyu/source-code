#!/usr/bin/ruby
# stmt.rb: demonstrate statement processing in Ruby
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

puts "Fetch using each as iterator (access columns by position)"
begin
#@ _FETCHLOOP_EACH_ITERATOR_
  result = client.query("SELECT id, name, cats FROM profile")
  result.each do |row|
    printf "id: %s, name: %s, cats: %s\n", row.values[0], row.values[1], row.values[2]
  end
  result.free
#@ _FETCHLOOP_EACH_ITERATOR_
rescue Mysql2::Error => e
  puts "Oops, the statement failed"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
end

puts "Fetch using each as iterator (access columns by name)"
begin
  result = client.query("SELECT id, name, cats FROM profile")
#@ _ACCESS_BY_NAME_
  result.each do |row|
    printf "id: %s, name: %s, cats: %s\n",
           row["id"], row["name"], row["cats"]
  end
  result.free
#@ _ACCESS_BY_NAME_
rescue Mysql2::Error => e
  puts "Oops, the statement failed"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
end

puts "Execute UPDATE statement"
begin
#@ _DO_1_
  count = client.query("UPDATE profile SET cats = cats+1 WHERE name = 'Sybil'")
  puts "Number of rows updated: #{client.affected_rows}"
#@ _DO_1_
rescue Mysql2::Error => e
  puts "Oops, the statement failed"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
end

client.close
