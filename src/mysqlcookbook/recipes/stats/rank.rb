#!/usr/bin/ruby
# rank.rb: assign ranks to a set of values

require "Cookbook"

client = Cookbook.connect()

# Assign ranks using position (row number) within the set of values,
# except that tied values all get the rank accorded the first of them.

#@ _ASSIGN_RANKS_
res = client.query("SELECT score FROM ranks ORDER BY score DESC")
rownum = 0
rank = 0
prev_score = nil
puts "Row\tRank\tScore\n"
res.each do |row|
  score = row.values[0]
  rownum += 1
  rank = rownum if rownum == 1 || prev_score != score
  prev_score = score
  puts "#{rownum}\t#{rank}\t#{score}"
end
#@ _ASSIGN_RANKS_

client.close()
