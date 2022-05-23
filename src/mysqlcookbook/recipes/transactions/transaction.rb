#!/usr/bin/ruby
# transaction.rb: simple transaction demonstration

# By default, this creates an InnoDB table.  If you specify a storage
# engine on the command line, that will be used instead.  Normally,
# this should be a transaction-safe engine that is supported by your
# server.  However, you can pass a nontransactional storage engine
# to verify that rollback doesn't work properly for such engines.

# The script uses a table named "money" and drops it if necessary.
# Change the name if you have a valuable table with that name. :-)

require "Cookbook"

# Create the example table and populate it with a couple of rows

def init_table(client, tbl_engine)
  begin
    client.query("DROP TABLE IF EXISTS money")
    client.query("CREATE TABLE money (name CHAR(5), amt INT, PRIMARY KEY(name)) ENGINE = " +
                              tbl_engine)
    client.query("INSERT INTO money (name, amt) VALUES('Eve', 10)")
    client.query("INSERT INTO money (name, amt) VALUES('Ida', 0)")
  rescue Mysql2::Error => e
    puts "Cannot initialize test table"
    puts "#{e.errno}: #{e.message}"
  end
end

# Display the current contents of the example table

def display_table(client)
  begin
      client.query("SELECT name, amt FROM money").each do |row|
      puts "#{row.values[0]} has $#{row.values[1]}"
    end
  rescue Mysql2::Error => e
    puts "Cannot display contents of test table"
    puts "#{e.errno}: #{e.message}"
  end
end

tbl_engine = "InnoDB" # default storage engine
tbl_engine = ARGV[0] if ARGV.length > 0

puts "Using storage engine #{tbl_engine} to test transactions"

client = Cookbook.connect

# Use commit()/rollback() methods

puts "----------"
puts "This transaction should succeed."
puts "Table contents before transaction:"
init_table(client, tbl_engine)
display_table(client)

#@ _DO_TRANSACTION_1_
begin
  client.query("START TRANSACTION")
  client.query("UPDATE money SET amt = amt - 6 WHERE name = 'Eve'")
  client.query("UPDATE money SET amt = amt + 6 WHERE name = 'Ida'")
  client.query("COMMIT")
rescue Mysql2::Error => e
  puts "Transaction failed, rolling back. Error was:"
  puts "#{e.errno}: #{e.message}"
  begin           # empty exception handler in case rollback fails
    client.query("ROLLBACK")
  rescue
  end
end
#@ _DO_TRANSACTION_1_

puts "Table contents after transaction:"
display_table(client)

puts "----------"
puts "This transaction should succeed."
puts "Table contents before transaction:"
init_table(client, tbl_engine)
display_table(client)

#@ _DO_TRANSACTION_2_
begin
  client.query("START TRANSACTION")
  client.query("UPDATE money SET amt = amt - 6 WHERE name = 'Eve'")
  client.query("UPDATE money SET amt = amt + 6 WHERE name = 'Ida'")
rescue Mysql2::Error => e
  puts "Transaction failed, rolling back. Error was:"
  puts "#{e.errno}: #{e.message}"
  begin
    client.query("ROLLBACK")
  rescue
  end
end
#@ _DO_TRANSACTION_2_

puts "Table contents after transaction:"
display_table(client)

puts "----------"
puts "This transaction should fail."
puts "Table contents before transaction:"
init_table(client, tbl_engine)
display_table(client)

begin
  client.query("START TRANSACTION")
  client.query("UPDATE money SET amt = amt - 6 WHERE name = 'Eve'")
  client.query("UPDATE money SET xamt = xamt + 6 WHERE name = 'Ida'")
  client.query("COMMIT")
rescue Mysql2::Error => e
  puts "Transaction failed, rolling back. Error was:"
  puts "#{e.errno}: #{e.message}"
  begin           # empty exception handler in case rollback fails
    client.query("ROLLBACK")
  rescue
  end
end

puts "Table contents after transaction:"
display_table(client)

puts "----------"
puts "This transaction should fail."
puts "Table contents before transaction:"
init_table(client, tbl_engine)
display_table(client)

begin
  client.query("START TRANSACTION")
  client.query("UPDATE money SET amt = amt - 6 WHERE name = 'Eve'")
  client.query("UPDATE money SET xamt = xamt + 6 WHERE name = 'Ida'")
  client.query("COMMIT")
rescue Mysql2::Error => e
  puts "Transaction failed, rolling back. Error was:"
  puts "#{e.errno}: #{e.message}"
  begin
    client.query("ROLLBACK")
  rescue
  end
end

puts "Table contents after transaction:"
display_table(client)

client.close
