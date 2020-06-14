#!/usr/bin/perl -w
#---
# Excerpted from "The Pragmatic Programmer, 20th Anniversary Edition",
# published by The Pragmatic Bookshelf.
# Copyrights apply to this code. It may not be used to create training material,
# courses, books, articles, and the like. Contact us if you are in doubt.
# We make no guarantees that this code is fit for any purpose.
# Visit http://www.pragmaticprogrammer.com/titles/tpp20 for more book information.
#---
use strict;

# From "Domain Languages",
# Parse a time in the format 
#
#  time -> hh am/pm   |
#          hh:mm      |
#          hh:mm am/pm
#
# print the number of minutes past midnight, or return -1 on error

$_ = shift;

/^(\d\d?)(am|pm)$/        && doTime($1, 0,  $2, 12);
/^(\d\d?):(\d\d)(am|pm)$/ && doTime($1, $2, $3, 12);
/^(\d\d?):(\d\d)$/        && doTime($1, $2,  0, 24);
die "Invalid time $_\n";

#
# doTime(hour, min, ampm, maxHour)
#
sub doTime($$$$) {
  my ($hour, $min, $offset, $maxHour) = @_;
  die "Invalid hour: $hour" if ($hour >= $maxHour);
  $hour += 12 if ($offset eq "pm");
  print $hour*60 + $min, " minutes past midnight\n";
  exit(0);
}
