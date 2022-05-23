#!/usr/bin/perl
# validate_misc.pl: Miscellaneous validation stuff, mostly pattern-matching.

use strict;
use warnings;
use Cookbook_Utils;

my $val;
my $valid;

print "Test: trim leading/trailing whitespace:\n";
foreach my $_val ("abc", "  abc", "abc  ", "  abc  ")
{
  my $val = $_val;
#@ _TRIM_WHITESPACE_
  $val =~ s/^\s+//;   # trim leading whitespace
  $val =~ s/\s+$//;   # trim trailing whitespace
#@ _TRIM_WHITESPACE_
  print "Original and trimmed values: ($_val) ($val)\n";
}

# examples of direct comparison against specific literal values

$val = "x";
#@ _DIRECT_1_
# require a nonempty value
$valid = ($val ne "");
# require a specific nonempty value
$valid = ($val eq "abc");
# require one of several values
$valid = ($val eq "abc" || $val eq "def" || $val eq "xyz");
#@ _DIRECT_1_
$val = 1;
#@ _DIRECT_2_
# require value in particular range (1 to 10)
$valid = ($val >= 1 && $val <= 10);
#@ _DIRECT_2_
#@ _STRING_CASE_INSENSITIVE_
# require a specific nonempty value in case-insensitive fashion
$valid = (lc ($val) eq lc ("AbC"));
#@ _STRING_CASE_INSENSITIVE_

# Use parentheses in a pattern to remember the matched substrings
my ($first_part, $the_rest);
#@ _REMEMBER_SUBSTRING_
if ("2019-05-23" =~ /^(\d+)(.*)$/)
{
  $first_part = $1; # this is the year, 2019
  $the_rest = $2;   # this is the rest of the date
}
#@ _REMEMBER_SUBSTRING_
print "first part: $first_part; the rest: $the_rest\n";

# Use ? to indicate optional parts of patterns

print "Test: digit sequence with optional leading minus and/or trailing dot\n";
foreach my $val ("123", "-123", "-123.", "123.", "--123", "123..", "abc")
{
  $valid = ($val =~
#@ _OPTIONAL_MINUS_PERIOD_
        /^-?\d+\.?$/
#@ _OPTIONAL_MINUS_PERIOD_
      );
  print "Value: $val; matches: " . ($valid ? "yes" : "no") . "\n"
}

# Use (...)? to group multiple optional elements

print "Test: Time in hh:mm format, optionally followed by AM or PM\n";
print "(optional part remembered)\n";
foreach my $val ("10:20", "10:20AM", "10:20 AM", "10:20 AMX",
        "10:20 PM", "10:20 pm")
{
  $valid = ($val =~
#@ _OPTIONAL_AM_PM_REMEMBERED_
        /^\d{1,2}:\d{2}\s*(AM|PM)?$/i
#@ _OPTIONAL_AM_PM_REMEMBERED_
      );
  print "Value: $val; matches: " . ($valid ? "yes" : "no");
  if ($valid)
  {
    print "; optional part: " . (defined ($1) ? $1 : "(there wasn't one)");
  }
  print "\n";
}

# Same test but use (?:pat), which doesn't remember the grouped elements

print "Test: Time in hh:mm format, optionally followed by AM or PM\n";
print "(optional part not remembered)\n";
foreach my $val ("10:20", "10:20AM", "10:20 AM", "10:20 AMX",
        "10:20 PM", "10:20 pm")
{
  $valid = ($val =~
#@ _OPTIONAL_AM_PM_NOT_REMEMBERED_
        /^\d{1,2}:\d{2}\s*(?:AM|PM)?$/i
#@ _OPTIONAL_AM_PM_NOT_REMEMBERED_
      );
  print "Value: $val; matches: " . ($valid ? "yes" : "no") . "\n";
}

# Loose integer matching.  Show two ways to accept a value that begins
# with an integer, followed by a possible nonnumeric suffix, then
# convert the value to a true number.

print "Test: integer, possibly followed by nonnumeric suffix\n";
foreach my $_val ("97", "97xyz", "xyz97")
{
  my $val;
  print "Test value: $_val\n";
  $val = $_val;
#@ _USE_MATCHING_SUBPART_
  if ($val =~ /^(\d+)/)
  {
    $val = $1;  # reset value to matched subpart
  }
#@ _USE_MATCHING_SUBPART_
  print "Value after subpart match test: $val\n";
  $val = $_val;
# EXPECT Perl to issue a warning for +0 operation below:
#@ _USE_PLUS_ZERO_
  if ($val =~ /^\d+/)
  {
    $val += 0;
  }
#@ _USE_PLUS_ZERO_
  # the value will be unchanged from the original here if the pattern failed
  print "Value after string-to-number-conversion: $val\n";
}

# Match parts of a date using parentheses so the subparts can be extracted

print "Test: match date and extract subparts\n";
foreach my $val ("2000-01-02", "00-01-02", "1999-12-13", "abc")
{
my ($year, $month, $day);
#@ _EXTRACT_DATE_SUBPARTS_
  if ($val =~ /^(\d{2,4})\D(\d{1,2})\D(\d{1,2})$/)
  {
    ($year, $month, $day) = ($1, $2, $3);
  }
#@ _EXTRACT_DATE_SUBPARTS_
  print "Date: $val";
  if (defined ($year))    # did the match succeed?
  {
    print "; subparts: ($year) ($month) ($day)";
  }
  else
  {
    print " (not a date)";
  }
  print "\n";
}

# Reformat time if it's missing the seconds part

print "Test: reformat time if missing seconds part\n";
foreach my $_val ("12:15:45", "2:15")
{
  my $val = $_val;
#@ _REFORMAT_TIME_
  if ($val =~ /^(\d{1,2}):(\d{2})(?::(\d{2}))?$/)
  {
    my ($hour, $min, $sec) = ($1, $2, $3);
    $sec = "00" if !defined ($sec); # seconds missing; use 00
    $val = "$hour:$min:$sec";
  }
#@ _REFORMAT_TIME_
  print "Original time: $_val\n";
  print "Reformatted time: $val\n";
}

# Perform conversion of 12-hour times with AM or PM to 24-hour times

print "Test: Convert 12-hour times with AM/PM to 24-hour times\n";
foreach my $_val ("8:20", "8:20 AM", "8:20 PM",
        "10:20:15 AM", "10:20:15 PM", "10:20:15 pm",
        "12:00:00 AM", "12:00:00 PM", "12:00:00",
        "12:59:59 AM", "12:59:59 PM", "12:59:59",
        "11:59:59 AM", "11:59:59 PM")
{
  my $val = $_val;
#@ _12_HOUR_TIME_TO_24_HOUR_TIME_
  if ($val =~ /^(\d{1,2}):(\d{2})(?::(\d{2}))?\s*(AM|PM)?$/i)
  {
    my ($hour, $min, $sec) = ($1, $2, $3);
    # supply missing seconds
    $sec = "00" unless defined ($sec);
    if ($hour == 12 && (!defined ($4) || uc ($4) eq "AM"))
    {
      $hour = "00"; # 12:xx:xx AM times are 00:xx:xx
    }
    elsif ($hour < 12 && defined ($4) && uc ($4) eq "PM")
    {
      $hour += 12;  # PM times other than 12:xx:xx
    }
    $val = "$hour:$min:$sec";
  }
#@ _12_HOUR_TIME_TO_24_HOUR_TIME_
  print "12-hour value: $_val; 24-hour value: $val\n";
}


$val = "9-01-01";
#@ _USE_IS_ISO_DATE_
my $ref = is_iso_date ($val);
if (defined ($ref))
{
  # $val matched ISO format pattern;
  # check its subparts using $ref->[0] through $ref->[2]
}
else
{
  # $val didn't match ISO format pattern
}
#@ _USE_IS_ISO_DATE_

print "Test: is_valid_date()\n";
$val = "2001-02-03";      # use known valid date here
$ref = is_iso_date ($val);
#@ _USE_IS_VALID_DATE_1_
$valid = is_valid_date ($ref->[0], $ref->[1], $ref->[2]);
#@ _USE_IS_VALID_DATE_1_
print "$val is valid: " . ($valid ? "yes" : "no") . "\n";
#@ _USE_IS_VALID_DATE_2_
$valid = is_valid_date (@{$ref});
#@ _USE_IS_VALID_DATE_2_
print "$val is valid: " . ($valid ? "yes" : "no") . "\n";

# More tests
print "More tests: is_valid_date()\n";
foreach my $val ('2100-02-29', '2000-02-29', '2000-13-01', '2000-04-31',
                 '1000')
{
  $ref = is_iso_date ($val);
  $valid = $ref ? is_valid_date ($ref->[0], $ref->[1], $ref->[2]) : undef;
  print "$val is valid: " . ($valid ? "yes" : "no") . "\n";
}

print "Test: is_valid_time()\n";
foreach my $val ('10:15:30', '10:60:30', '24:15:30', '10:15:60')
{
  my $ref = is_24hr_time ($val);
  $valid = $ref ? is_valid_time ($ref->[0], $ref->[1], $ref->[2]) : undef;
  print "$val is valid: " . ($valid ? "yes" : "no") . "\n";
}

print "Test: rewrite date with substitution operation\n";
$val = "12-31-99";      # date in MM-DD-YY format
print "Original MM-DD-YY value: $val\n";
#@ _DATE_SUBST_REWRITE_
$val =~ s/^(\d+)\D(\d+)\D(\d+)$/$3-$1-$2/;
#@ _DATE_SUBST_REWRITE_
print "Rewritten YY-MM-DD value: $val\n";

print "Test: is_24hr_time(), is_ampm_time()\n";
foreach my $val ("8:20:15", "8:20:15 AM", "8:20:15 PM",
        "10:20:15 AM", "10:20:15 PM", "10:20:15 pm")
{
  print "Value: $val";
  my $ref = is_24hr_time ($val);
  print " is_24hr_time(): " . (defined ($ref) ? "yes" : "no");
  $ref = is_ampm_time ($val);
  print " is_ampm_time(): " . (defined ($ref) ? "yes" : "no");
  print "\n";
}

# Test array membership.

my @members = ("red", "green", "blue");

print "\nArray membership test\n";
print "Members in array: @members\n";

foreach my $val ("red", "Red", "white")
{
  my $valid;

  # case sensitive test:
#@ _ARRAY_TEST_CASE_SENSITIVE_
  $valid = grep (/^$val$/, @members);
#@ _ARRAY_TEST_CASE_SENSITIVE_
  print "Value: $val\n";
  print "Valid (case sensitive): " . ($valid ? "yes" : "no") . "\n";

  # case insensitive test:
#@ _ARRAY_TEST_CASE_INSENSITIVE_
  $valid = grep (/^$val$/i, @members);
#@ _ARRAY_TEST_CASE_INSENSITIVE_
  print "Value: $val\n";
  print "Valid (case insensitive): " . ($valid ? "yes" : "no") . "\n";
}

print "Test: credit card number 16 digits long\n";
foreach my $_val (  "0123456789012345",
                    "0123 4567 8901 2345",
                    "0123-4567-8901-2345",
                    "0123-4567-8901-234")
{
  my $val = $_val;
  print "Original: $_val\n";
  my $valid = ($val =~
#@ _CC_VALID_BASED_ON_PAT_ONLY_
            /^[- \d]+/
#@ _CC_VALID_BASED_ON_PAT_ONLY_
          );
  print "Valid (based on pattern match only): "
        . ($valid ? "yes" : "no") . "\n";
#@ _STRIP_NON_DIGITS_
  $val =~ s/\D//g;
  $valid = (length ($val) == 16);
#@ _STRIP_NON_DIGITS_
  print "With nondigits stripped: $val\n";
  print "Valid (based on pattern and length tests): "
        . ($valid ? "yes" : "no") . "\n";
}
