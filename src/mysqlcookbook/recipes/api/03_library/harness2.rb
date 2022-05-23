#!/usr/bin/ruby
# harness2.rb: test harness for Cookbook.rb library

# Does not catch exceptions, so this script simply dies if
# a connect error occurs.

require "Cookbook"

#@ _FRAG_
client = Cookbook.connect
print "Connected\n"
client.close
print "Disconnected\n"
#@ _FRAG_
