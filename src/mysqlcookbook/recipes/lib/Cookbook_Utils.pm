package Cookbook_Utils;
# Cookbook_Utils.pm: MySQL Cookbook utilities

require Exporter;
@ISA = qw(Exporter);
@EXPORT = qw(
  check_enum_value
  check_set_value
  get_column_names
  get_column_info
  get_enumorset_info
  trim_whitespace
  is_integer
  is_unsigned_integer
  is_positive_integer
  is_innings_pitched
  is_mmddyy_date
  is_ddmmyy_date
  is_iso_date
  is_leap_year
  is_valid_date
  is_valid_time
  is_24hr_time
  is_ampm_time
  yy_to_yyyy
  days_in_month
);

use strict;
use warnings;
use DBI;

# Given database and table names, return an array containing the names
# of the table's columns, in table definition order.
# Return empty array if an error occurs.

#@ _GET_COLUMN_NAMES_
sub get_column_names
{
my ($dbh, $db_name, $tbl_name) = @_;

  my $stmt = qq{
    SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS
    WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?
    ORDER BY ORDINAL_POSITION
  };
  my $ref = $dbh->selectcol_arrayref ($stmt, undef, $db_name, $tbl_name);
  return defined ($ref) ? @{$ref} : ();
}
#@ _GET_COLUMN_NAMES_

# Given database and table names, return information about the table columns.
# Return value is a reference to a hash keyed by column name. Each hash
# element is a reference to a hash keyed by name of column in the
# INFORMATION_SCHEMA.COLUMNS table.
# Return undef if an error occurs.

#@ _GET_COLUMN_INFO_
sub get_column_info
{
my ($dbh, $db_name, $tbl_name) = @_;

  my $stmt = qq{
    SELECT * FROM INFORMATION_SCHEMA.COLUMNS
    WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ?
  };
  return $dbh->selectall_hashref ($stmt, "COLUMN_NAME",
                                  undef, $db_name, $tbl_name);
}
#@ _GET_COLUMN_INFO_

# get_enumorset_info() - get metadata for an ENUM or SET column.
# Take a database connection and database, table, and column names.
# Return a reference to a hash keyed by "name", "type", "values", "nullable",
# and "default". Return undef if no info available.

#@ _GET_ENUMORSET_INFO_
sub get_enumorset_info
{
my ($dbh, $db_name, $tbl_name, $col_name) = @_;
my $info = {};

  my @row = $dbh->selectrow_array (qq{
              SELECT COLUMN_NAME, COLUMN_TYPE, IS_NULLABLE, COLUMN_DEFAULT
              FROM INFORMATION_SCHEMA.COLUMNS
              WHERE TABLE_SCHEMA = ? AND TABLE_NAME = ? AND COLUMN_NAME = ?
            }, undef, $db_name, $tbl_name, $col_name
      );
  return undef unless @row; # no such column
  $info->{name} = $row[0];
  return undef unless $row[1] =~ /^(ENUM|SET)\((.*)\)$/i; # not ENUM or SET
  $info->{type} = $1;
  # split value list on commas, trim quotes from end of each word
  my @val = split (",", $2);
  s/^'(.*)'$/$1/ foreach (@val);
  $info->{values} = [ @val ];
  # determine whether column can contain NULL values
  $info->{nullable} = (uc ($row[2]) eq "YES");
  # get default value (undef represents NULL)
  $info->{default} = $row[3];

  return $info;
}
#@ _GET_ENUMORSET_INFO_


# Check whether a value is a legal ENUM value.

#@ _CHECK_ENUM_VALUE_
sub check_enum_value
{
my ($dbh, $db_name, $tbl_name, $col_name, $val) = @_;

  my $valid = 0;
  my $info = get_enumorset_info ($dbh, $db_name, $tbl_name, $col_name);
  if ($info && uc ($info->{type}) eq "ENUM")
  {
    # use case-insensitive comparison because default collation
    # (latin1_swedish_ci) is case-insensitive (adjust if you use
    # a different collation)
    $valid = grep (/^$val$/i, @{$info->{values}});
  }
  return $valid;
}
#@ _CHECK_ENUM_VALUE_


# Check whether a value is a legal SET value; each element must be
# a legal element of the column.  (For example, 'blue,white' is a legal
# value for a set defined as 'red,white,blue'.)

# An empty string is always a legal set element.  No special test
# is required, because for the empty value, split returns an empty
# list and the loop never executes.

#@ _CHECK_SET_VALUE_
sub check_set_value
{
my ($dbh, $db_name, $tbl_name, $col_name, $val) = @_;

  my $valid = 0;
  my $info = get_enumorset_info ($dbh, $db_name, $tbl_name, $col_name);
  if ($info && uc ($info->{type}) eq "SET")
  {
    return 1 if $val eq "";    # empty string is legal element
    # use case-insensitive comparison because default collation
    # (latin1_swedish_ci) is case-insensitive (adjust if you use
    # a different collation)
    $valid = 1;     # assume valid until we find out otherwise
    foreach my $v (split (/,/, $val))
    {
      if (!grep (/^$v$/i, @{$info->{values}}))
      {
        $valid = 0; # value contains an invalid element
        last;
      }
    }
  }
  return $valid;
}
#@ _CHECK_SET_VALUE_


# Trim whitespace from the beginning and end of a string, returning
# the result.

#@ _TRIM_WHITESPACE_
sub trim_whitespace
{
my $s = $_[0];

  $s =~ s/^\s+//;   # trim leading whitespace
  $s =~ s/\s+$//;   # trim trailing whitespace
  return $s;
}
#@ _TRIM_WHITESPACE_


# Return true if argument represents an integer (possible leading sign),
# an unsigned (nonnegative) integer, or a positive integer.

#@ _IS_INTEGER_
sub is_integer
{
my $s = $_[0];

  return $s =~ /^[-+]?\d+$/;
}
#@ _IS_INTEGER_

#@ _IS_UNSIGNED_INTEGER_
sub is_unsigned_integer
{
my $s = $_[0];

  return $s =~ /^\d+$/;
}
#@ _IS_UNSIGNED_INTEGER_

#@ _IS_POSITIVE_INTEGER_
sub is_positive_integer
{
my $s = $_[0];

  return $s =~ /^\+?\d+$/ && $s > 0;
}
#@ _IS_POSITIVE_INTEGER_


# Return true if argument represents a valid innings-pitched number
# (.1, 1, 1.2, etc.  Fractional digit, if present, must be 0, 1, or 2.)

#@ _IS_INNINGS_PITCHED_
sub is_innings_pitched
{
my $s = $_[0];

  return $s =~ /^(\d+(\.[012]?)?|\.[012])$/;
}
#@ _IS_INNINGS_PITCHED_


# Functions to check whether a string looks like a date in various
# common formats.  All permit the year to be 2 or 4 digits.  All permit
# delimiters to be any nondigit character.

# Each returns undef if date doesn't match the pattern, otherwise returns
# a reference to an array containing the year, month, and day parts.
# Does not perform bounds testing on the parts.

#@ _IS_ISO_DATE_
sub is_iso_date
{
my $s = $_[0];

  return undef unless $s =~ /^(\d{2,4})\D(\d{1,2})\D(\d{1,2})$/;
  return [ $1, $2, $3 ];  # return year, month, day
}
#@ _IS_ISO_DATE_

#@ _IS_MMDDYY_DATE_
sub is_mmddyy_date
{
my $s = $_[0];

  return undef unless $s =~ /^(\d{1,2})\D(\d{1,2})\D(\d{2,4})$/;
  return [ $3, $1, $2 ];  # return year, month, day
}
#@ _IS_MMDDYY_DATE_

#@ _IS_DDMMYY_DATE_
sub is_ddmmyy_date
{
my $s = $_[0];

  return undef unless $s =~ /^(\d{1,2})\D(\d{1,2})\D(\d{2,4})$/;
  return [ $3, $2, $1 ];  # return year, month, day
}
#@ _IS_DDMMYY_DATE_

# Functions to check whether a string looks like a time in 24-hour
# format, or 12-hour format with an optional AM/PM suffix.  (Note that a
# 12-hour time like 12:00:00 PM becomes a 24-hour time like 12:00:00, not
# 24:00:00. And 12:xx:xx AM is 00:xx:xx in 24-hour time)
# The hour can be 1 or 2 digits.  The minute and second must be two digits.
# Delimiters can any nondigit character.

#@ _IS_24HR_TIME_
sub is_24hr_time
{
my $s = $_[0];

  return undef unless $s =~ /^(\d{1,2})\D(\d{2})\D(\d{2})$/;
  return [ $1, $2, $3 ];  # return hour, minute, second
}
#@ _IS_24HR_TIME_

#@ _IS_AMPM_TIME_
sub is_ampm_time
{
my $s = $_[0];

  return undef unless $s =~ /^(\d{1,2})\D(\d{2})\D(\d{2})(?:\s*(AM|PM))?$/i;
  my ($hour, $min, $sec) = ($1, $2, $3);
  if ($hour == 12 && (!defined ($4) || uc ($4) eq "AM"))
  {
    $hour = "00"; # 12:xx:xx AM times are 00:xx:xx
  }
  elsif ($hour < 12 && defined ($4) && uc ($4) eq "PM")
  {
    $hour += 12;  # PM times other than 12:xx:xx
  }
  return [ $hour, $min, $sec ]; # return hour, minute, second
}
#@ _IS_AMPM_TIME_

# Determine whether a year is a leap year.  Requires 4-digit
# year value (e.g., "1993", not "93").

#@ _IS_LEAP_YEAR_
sub is_leap_year
{
my $year = $_[0];

  return ($year % 4 == 0) && ((($year % 100) != 0) || ($year % 400) == 0);
}
#@ _IS_LEAP_YEAR_


# Given an array of integers representing year, month, and day of a date,
# determine whether the date is valid.

#@ _IS_VALID_DATE_
sub is_valid_date
{
my ($year, $month, $day) = @_;

  # year must be nonnegative, month and day must be positive
  return 0 if $year < 0 || $month < 1 || $day < 1;
  # check maximum limits on individual parts
  return 0 if $year > 9999
              || $month > 12
              || $day > days_in_month ($year, $month);
  return 1;
}
#@ _IS_VALID_DATE_


# Given an array of integers representing hour, minute, and second,
# determine whether the time is valid.

#@ _IS_VALID_TIME_
sub is_valid_time
{
my ($hour, $minute, $second) = @_;

  # values must be nonnegative
  return 0 if $hour < 0 || $minute < 0 || $second < 0;
  # check maximum limits on individual parts
  return 0 if $hour > 23 || $minute > 59 || $second > 59;
  return 1;
}
#@ _IS_VALID_TIME_


# Convert 2-digit year to 4 digits (return unchanged if not 2-digits).
# The optional second argument indicates the transition point at which
# values change from 2000-based to 1900-based.  The default is to switch
# at 70, like MySQL.  (Thus 00..69 -> 2000..2069 and 70..99 -> 1970..1999)

#@ _YY_TO_YYYY_
sub yy_to_yyyy
{
my ($year, $transition_point) = @_;

  $transition_point = 70 unless defined ($transition_point);
  $year += ($year >= $transition_point ? 1900 : 2000) if $year < 100;
  return $year;
}
#@ _YY_TO_YYYY_


# Given year and month, return the number of days in the month.  Year
# value must be in 4-digit form or the leap-year test won't be correct.

#@ _DAYS_IN_MONTH_
sub days_in_month
{
my ($year, $month) = @_;
my @day_tbl = (31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31);
my $days = $day_tbl[$month-1];

  # add a day for Feb of leap years
  $days++ if $month == 2 && is_leap_year ($year);
  return $days;
}
#@ _DAYS_IN_MONTH_

1;  # return true
