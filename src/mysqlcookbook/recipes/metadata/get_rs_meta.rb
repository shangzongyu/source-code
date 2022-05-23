#!/usr/bin/ruby
# get_rs_meta.rb: run a statement and display its result set metadata

# The program runs a default statement, which can be overridden by supplying
# a statement as an argument on the command line.

require "Cookbook"

#@ _DEFAULT_STATEMENT_
stmt = "SELECT name, birth FROM profile"
#@ _DEFAULT_STATEMENT_
# override statement with command line argument if one was given
stmt = ARGV[0] if ARGV.length > 0

begin
  client = Cookbook.connect
rescue Mysql2::Error => e
  puts "Could not connect to server"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
end

begin
#@ _DISPLAY_METADATA_
  puts "Statement: #{stmt}"
  sth = client.prepare(stmt)
  res = sth.execute()
  # metadata information becomes available at this point ...
  puts "Number of columns: #{res.fields.size}"
  puts "Note: statement has no result set" if res.count == 0
  puts "Columns names: #{res.fields.join(", ")}"
  res.free
#@ _DISPLAY_METADATA_
rescue Mysql2::Error => e
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
end

client.close
