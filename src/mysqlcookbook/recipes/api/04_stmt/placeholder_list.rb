#!/usr/bin/ruby
# placeholder_list.rb

# Create a string of placeholder characters, with one ? character
# per element in an array of values.

# Array of values

values = [1, 2, 3, 4, 5]

# Method 1: use * to "multiply" and array and join to put commas between
# elements

#@ _JOIN_METHOD_
str = (["?"] * values.size).join(",")
#@ _JOIN_METHOD_

puts "Method 1: #{str}"

# Method 2: successive concatenation

#@ _CONCAT_METHOD_1_
str = "?" if values.size
1.upto(values.size-1) { str << ",?" }
#@ _CONCAT_METHOD_1_

puts "Method 2: #{str}"
