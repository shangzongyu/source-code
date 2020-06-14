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

# Call with the name of the program to test

my $prog = shift or die "Missing program to test";

# Test all the combinations of time accepted to the time parser

$| = 1;
# Test 1. Test <hour>am|pm

print "hh am|pm    ";
for (my $hour = 0; $hour < 12; $hour++) {
  check("$ {hour}am", 60*$hour);
  check("$ {hour}pm", 60*($hour+12));
  print "..";
}

# Test 2. Out of bounds <hour>am|pm

check("13am", -1); check("12pm", -1); check("999am", -1);

print "\n";

# Test 3. Check hh:mm times

my $ans = 0;

print "hh:mm       ";

for (my $hour = 0; $hour < 24; $hour++) {
  print ".";
  for (my $min = "00"; $min lt "60"; $min++) {
    check("$hour:$min", $ans);
    $ans++;
  }
}
print "\n";

# TEst 4. hh:mm am/pm times

$ans = 0;
print "hh:mm am/pm ";
for (my $hour = 0; $hour < 12; $hour++) {
  print "..";
  for (my $min = "00"; $min lt "60"; $min++) {
    check("$hour:$ {min}am", $ans);
    check("$hour:$ {min}pm", $ans+12*60);
    $ans++;
  }
}
print "\n";

# finally some silly values

check("24:00", -1); check("goofy", -1); check("1:1", -1);
check("1:0023", -1); check("13:34am", -1);

#
# Run timeparser on arg1, check result is arg2
#
sub check($$) {
  my $time = shift;
  my $expected = shift;
  my $result = `$prog $time 2>/dev/null`;
  my ($got) = split ' ', $result;

  if ($expected < 0) {
    if ($? == 0) {
      die "$prog $time -> should have failed, but returned $got";
    }
  }
  elsif ($got != $expected) {
    die "$prog $time  -> returned $got, expected $expected";
  }
}
  
