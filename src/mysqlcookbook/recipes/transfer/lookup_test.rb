#!/usr/bin/ruby
# lookup_test.rb: Demonstrate use of hash for lookup/validation purposes.

# create hash, add members to it, using values as keys

members = Hash[
  "pig"   => 1,
  "cat"   => 1,
  "duck"  => 1,
  "dog"   => 1,
]

# show list of legal values

puts "Legal values: " + members.keys.sort.join(" ")

# test some values to see whether they're in the hash

puts "Test some values:"
["cat", "snake"].each do |val|
  if members.has_key?(val)
    puts val + " (good)"
  else
    puts val + " (bad)"
  end
end
