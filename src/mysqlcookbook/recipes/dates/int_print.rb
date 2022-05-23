#!/usr/bin/ruby
# int_print.rb: print time intervals in hours, minutes, seconds

require "Cookbook"

dbh = Cookbook.connect()

#@ _TIME_COMPONENTS_
def time_components(time_in_secs)
  if time_in_secs < 0
    sign = "-"
    time_in_secs = -time_in_secs
  else
    sign = ""
  end
  hours = (time_in_secs / 3600).to_i
  minutes = ((time_in_secs / 60)).to_i % 60
  seconds = time_in_secs % 60
  return sign, hours, minutes, seconds
end
#@ _TIME_COMPONENTS_

begin
#@ _PRINT_INTERVALS_
  stmt = "SELECT t1, t2, TIME_TO_SEC(t2) - TIME_TO_SEC(t1) FROM time_val"
  dbh.execute(stmt) do |sth|
    sth.fetch do |row|
    t1, t2, interval = row
      sign, hours, minutes, seconds = time_components(interval)
      printf "t1 = %s, t2 = %s, interval = %s%d h, %d m, %d s\n",
              t1, t2, sign, hours, minutes, seconds
    end
  end
#@ _PRINT_INTERVALS_
rescue DBI::DatabaseError => e
  puts "Error code: #{e.err}"
  puts "Error message: #{e.errstr}"
end

dbh.disconnect()
