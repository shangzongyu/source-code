#!/usr/bin/ruby
# placeholder.rb: demonstrate statement processing in Ruby
# (with placeholders)

require "Cookbook"

begin
  client = Cookbook.connect
rescue Mysql2::Error => e
  puts "Cannot connect to server"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
  exit(1)
end

# Pass data values directly to query()

puts "Execute INSERT statement"
begin
#@ _PLACEHOLDER_QUERY_
  name = "De'Mont"
  birth = "1973-01-12"
  color = nil
  foods = "eggroll"
  cats = 4
  client.query("INSERT INTO profile (name,birth,color,foods,cats)
                  VALUES(#{name},#{birth},#{color},#{foods},#{cats})")
#@ _PLACEHOLDER_QUERY_
  puts "Number of rows inserted: #{client.affected_rows}"
rescue Mysql2::Error => e
  puts "Oops, the statement failed"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
end

# Prepare a statement, then pass the statement and data values to execute()

puts "Execute INSERT statement with prepare() + execute()"
begin
#@ _PLACEHOLDER_PREPARE_EXECUTE_1_
  sth = client.prepare("INSERT INTO profile (name,birth,color,foods,cats)
                     VALUES(?,?,?,?,?)")
  sth.execute("De'Mont", "1973-01-12", nil, "eggroll", 4)
#@ _PLACEHOLDER_PREPARE_EXECUTE_1_
  puts "Number of rows inserted: #{client.affected_rows}"
rescue Mysql2::Error => e
  puts "Oops, the statement failed"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
end

puts "Execute SELECT statement with placeholder"
begin
#@ _PLACEHOLDER_PREPARE_EXECUTE_2_
  sth = client.prepare("SELECT * FROM profile WHERE cats > ?")
  result = sth.execute(2)
  result.each do |row|
    printf "id: %s, name: %s, cats: %s\n", row["id"], row["name"], row["cats"]
  end
  sth.close
#@ _PLACEHOLDER_PREPARE_EXECUTE_2_
rescue Mysql2::Error => e
  puts "Oops, the statement failed"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
end

puts "Construct INSERT statement using escape()"
begin
#@ _QUOTE_
  stmt = sprintf "INSERT INTO profile (name,birth,color,foods,cats)
                  VALUES('%s','%s',%s,'%s',%s)",
                 client.escape("De'Mont"),
                 client.escape("1973-01-12"),
                 client.escape("NULL"),
                 client.escape("eggroll"),
                 4
  client.query(stmt)
#@ _QUOTE_
  puts "Statement:"
  puts stmt
  puts "Number of rows inserted: #{client.affected_rows}"
rescue Mysql2::Error => e
  puts "Oops, the statement failed"
  puts "Error code: #{e.errno}"
  puts "Error message: #{e.message}"
end

client.close
