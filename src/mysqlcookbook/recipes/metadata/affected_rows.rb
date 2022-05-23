#!/usr/bin/ruby
# affected_rows.rb

require "Cookbook"

stmt = "UPDATE profile SET cats = cats+1 WHERE name = 'Sybil'"

begin
  client = Cookbook.connect
rescue Mysql2::Error => e
  puts "Could not connect to server"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
end

# execute statement using do
#@ _FRAG_1_
client.query(stmt)
puts "Number of rows affected: #{client.affected_rows}"
#@ _FRAG_1_

# execute statement using prepare plus execute
#@ _FRAG_2_
sth = client.prepare(stmt)
sth.execute
puts "Number of rows affected: #{sth.affected_rows}"
#@ _FRAG_2_

client.close

# illustrate use of mysql_client_found_rows
#@ _MYSQL_CLIENT_FOUND_ROWS_
client = Mysql2::Client.new(:database => "cookbook",
                            :host => "localhost",
                            :username => "cbuser",
                            :password => "cbpass",
                            :flags => Mysql2::Client::FOUND_ROWS)
#@ _MYSQL_CLIENT_FOUND_ROWS_

# this statement changes no rows, but the row count should still
# be nonzero due to the use of mysql_client_found_rows
stmt = "UPDATE limbs SET arms = 0 WHERE arms = 0"
client.query(stmt)
puts "Number of rows matched: #{client.affected_rows}"
client.close
