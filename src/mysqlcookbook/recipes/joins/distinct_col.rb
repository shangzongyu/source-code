#!/usr/bin/ruby
# distinct_col.rb: resolve ambiguous join output column names using aliases

require "Cookbook"

begin
  client = Cookbook.connect
rescue Mysql2::Error => e
  puts "Could not connect to server"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
end


# First demonstrate the problem using a query that returns nonunique
# column names.

#@ _FRAG_1_
stmt = "
  SELECT artist.name, painting.title, states.name, painting.price
  FROM artist INNER JOIN painting INNER JOIN states
  ON artist.a_id = painting.a_id AND painting.state = states.abbrev
"
res = client.query(stmt)
# Determine the number of columns in result set rows two ways:
# - Check sth.column_names.size
# - Fetch a row into a hash and see how many keys the hash contains
count1 = res.fields.size
res.each do |row|
  count2 = row.keys.size
  puts "The statement is: #{stmt}"
  puts "According to column_names_size, the result set has #{count1} columns"
  puts "The column names are: " +
       res.fields.sort.join(",")
  puts "According to the row hash size, the result set has #{count2} columns"
  puts "The column names are: " + row.keys.sort.join(",")
  puts "The counts DO NOT match!" if count1 != count2
  break
end
#@ _FRAG_1_
res.free

puts ""

# Assign column aliases to provide distinct names

#@ _FRAG_2_
stmt = "
  SELECT
    artist.name AS painter, painting.title,
    states.name AS state, painting.price
  FROM artist INNER JOIN painting INNER JOIN states
  ON artist.a_id = painting.a_id AND painting.state = states.abbrev
"
res = client.query(stmt)
# Determine the number of columns in result set rows two ways:
# - Check sth.column_names.size
# - Fetch a row into a hash and see how many keys the hash contains
count1 = res.fields.size
res.each do |row|
  count2 = row.keys.size
  puts "The statement is: #{stmt}"
  puts "According to column_names_size, the result set has #{count1} columns"
  puts "The column names are: " +
       res.fields.sort.join(",")
  puts "According to the row hash size, the result set has #{count2} columns"
  puts "The column names are: " + row.keys.sort.join(",")
  puts "The counts DO NOT match!" if count1 != count2
  break
end
#@ _FRAG_2_
res.free

client.close
