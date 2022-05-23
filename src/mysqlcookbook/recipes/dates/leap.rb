#!/usr/bin/ruby
# leap.rb: Leap-year test of ISO date strings

# days_in_month - given an ISO-format date, determine the number
# of days in the month in which the date occurs

#@ _DAYS_IN_MONTH_
def days_in_month(date)
  year = date[0..3].to_i
  month = date[5..6].to_i   # month, 1-based
  days_in_month = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
  days = days_in_month[month-1]
  is_leap = (year.modulo(4) == 0) &&
              (year.modulo(100) != 0 || year.modulo(400) == 0)

  # add a day for Feb of leap years
  days += 1 if month == 2 && is_leap
  return days
end
#@ _DAYS_IN_MONTH_

# set up an array of test dates

date_array = [
  "1899-01-01",
  "1900-01-01",
  "1999-01-01",
  "2000-01-01",
  "1963-01-01",
  "1964-01-01",
]

date_array.each do |date|
#@ _LEAP_TEST_
  year = date[0..3].to_i
  is_leap = (year.modulo(4) == 0) &&
              (year.modulo(100) != 0 || year.modulo(400) == 0)
#@ _LEAP_TEST_
  puts "#{date} #{year} #{is_leap}"
#@ _YEAR_LENGTH_TEST_
  year = date[0..3].to_i
  is_leap = (year.modulo(4) == 0) &&
              (year.modulo(100) != 0 || year.modulo(400) == 0)
  days_in_year = (is_leap ? 366 : 365)
#@ _YEAR_LENGTH_TEST_
  puts "#{date} #{year} #{days_in_year} days"
end

[date_array, "1900-02-01", "1999-02-01", "2000-02-01"].flatten.each do |date|
  puts "Month for #{date} has #{days_in_month(date)} days"
end
