#!/usr/bin/ruby
# date_sent.rb: fetch rows, refer to columns by name

require "Cookbook"

client = Cookbook.connect

#@ _FRAG_
res = client.query("SELECT srcuser,
                   DATE_FORMAT(t,'%M %e, %Y') AS date_sent
                   FROM mail")
res.each do |row|
  printf "user: %s, date sent: %s\n", row["srcuser"], row["date_sent"]
end
res.free
#@ _FRAG_

client.close
