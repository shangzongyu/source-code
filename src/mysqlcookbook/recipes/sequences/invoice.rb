#!/usr/bin/ruby
# invoice.rb: multiple-table insert where both tables have an AUTO_INCREMENT
# column.  Save master table AUTO_INCREMENT value before inserting detail
# records to avoid losing it.

require "Cookbook"

begin
  client = Cookbook.connect
rescue DBI::DatabaseError => e
  puts "Cannot connect to server"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
  exit(1)
end

#@ _FRAG_
client.query("INSERT INTO invoice (inv_id,date) VALUES(NULL,CURDATE())")
inv_id = client.last_id
sth = client.prepare("INSERT INTO inv_item (inv_id,qty,description)
                   VALUES(?,?,?)")
sth.execute(inv_id, 1, "hammer")
sth.execute(inv_id, 3, "nails, box")
sth.execute(inv_id, 12, "bandage")
#@ _FRAG_

client.close
