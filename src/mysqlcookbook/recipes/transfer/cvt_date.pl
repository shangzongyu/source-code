#!/usr/bin/perl
# cvt_date.pl: Read input data, look for values that match a date
# format, convert them to another format. Also converts 2-digit
# years to 4-digit years on request. By default, assumes a
# transition point of 70, but this can be changed.

# Assumes tab-delimited, linefeed-terminated input lines.

# To add another format:
# - Modify argument processing code
# - Add a case to the input value test
# - Add a case to the output date formatting test

# Shortcoming: Doesn't accommodate trailing times (for date/time values)

use strict;
use warnings;
use Getopt::Long;
$Getopt::Long::ignorecase = 0; # options are case sensitive
$Getopt::Long::bundling = 1;   # permit short options to be bundled

sub check_date_format
{
my ($format, $type) = @_;

  return "iso" if $format =~ /^iso/i;
  return "us" if $format =~ /^us/i;
  return "british" if $format =~ /^br/i;
  die "Invalid $type date format: $format\n";
}

# Determine whether a year is a leap year.  Requires 4-digit
# year value (e.g., "1993", not "93").

sub is_leap_year
{
my $year = shift;

  return ($year % 4 == 0) && ((($year % 100) != 0) || ($year % 400) == 0);
}

# Given year and month, return the number of days in the month.  Year
# value must be in 4-digit form or the leap-year test won't be correct.

sub days_in_month
{
my ($year, $month) = @_;
my @day_tbl = (31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31);
my $days = $day_tbl[$month-1];

  # add a day for Feb of leap years
  $days++ if $month == 2 && is_leap_year ($year);
  return $days;
}

# Given an array of integers representing year, month, and day of a date,
# determine whether the date is valid.

sub is_valid_date
{
my ($year, $month, $day) = @_;

  # year must be nonnegative, month and day must be positive
  return 0 if $year < 0 || $month < 1 || $day < 1;
  # check maximum limits on individual parts
  return 0 if $year > 9999;
  return 0 if $month > 12;
  return 0 if $day > days_in_month ($year, $month);
  return 1;
}

my $prog = "cvt_date.pl";
my $usage = <<EOF;
Usage: $prog [ options ] [ data_file ]

Options:
--help
    Print this message
--iformat=format_name, --if=format_name
    Set date format for input (iso, us, british; default is iso)
--oformat=format_name, --of=format_name
    Set date format for output (iso, us, british; default is iso)
--warn
    Warn about bad dates
--add-century
    Convert 2-digit years to 4 digits
--transition
    Within-century transition point for 2-digit to 4-digit conversion
    (implies --add-century); default is 70
--columns=column_list
    Convert only specific columns; column_list is a comma-separated list
    of column numbers (first column is numbered 1)

Other arguments:
data_file
    Name of data file to convert
EOF

my $help;

my $iformat;     # input format
my $oformat;     # output format
my $warn;        # issue warnings about bad date
my $add_century; # convert 2-digit years to 4 digits
my $transition;  # transition at which 2-digit years are assumed to be 19XX
my $columns;     # check only these columns

GetOptions (
  # =s means a string value is required after the option
  "help"          => \$help,        # print help message
  "if=s"          => \$iformat,     # set input format only
  "iformat=s"     => \$iformat,     # ditto
  "of=s"          => \$oformat,     # set output format only
  "oformat=s"     => \$oformat,     # ditto
  "warn"          => \$warn,        # warn about bad dates
  "add-century"   => \$add_century, # convert 2-digit years to 4 digits
  "transition=n"  => \$transition,  # within-century transition point
                    # (implies --add-century)
  "columns=s"     => \$columns      # check only specific columns
) or die "$usage\n";

die "$usage\n" if defined ($help);

$iformat = "iso" unless defined ($iformat);     # set default format
$oformat = "iso" unless defined ($oformat);
$iformat = check_date_format ($iformat, "input");
$oformat = check_date_format ($oformat, "output");

$transition = 70 unless defined ($transition);    # set default transition

# 2-digit years don't provide accurate leap year testing
warn "NOTE: --warn without --add-century may produce spurious warnings\n"
                      if $warn && !$add_century;

my %columns;
if (defined ($columns))
{
  # make sure column specifiers are positive integers and hash them
  # (also convert from 1-based to 0-based values)
  foreach my $i (split (/,/, $columns))
  {
    if ($i =~ /^\d+$/)        # single column number
    {
      die "Column specifier $i is not a positive integer\n"
          unless $i > 0;
      $columns{$i-1} = 1;
    }
    elsif ($i =~ /^(\d+)-(\d+)$/) # column range m-n
    {
      my ($begin, $end) = ($1, $2);
      die "$i is not a valid column specifier\n"
          unless $begin > 0 && $end > 0 && $begin <= $end;
      while ($begin <= $end)
      {
        $columns{$begin-1} = 1;
        ++$begin;
      }
    }
    else
    {
      die "$i is not a valid column specifier\n";
    }
  }
}
$columns = defined ($columns);  # use as boolean flag from this point

# format for sprintf'ing year values; width depends on whether
# or not 2-digit to 4-digit conversion was requested

my $yearfmt = ($add_century ? "%04d" : "%02d");

my ($y, $m, $d);

while (<>)
{
  chomp;
  my @val = split (/\t/, $_, 10000);  # split, preserving all fields
  for my $i (0 .. @val - 1)
  {
    # don't process the value if a column list was
    # specified but this column isn't one of them
    next if $columns && !exists ($columns{$i});

    my $val = $val[$i];
    if ($iformat eq "iso"
      && $val =~ /^(\d{2}|\d{4})\D(\d{1,2})\D(\d{1,2})$/)
    {
      ($y, $m, $d) = ($1, $2, $3);
    }
    elsif ($iformat eq "us"
      && $val =~ /^(\d{1,2})\D(\d{1,2})\D(\d{2}|\d{4})$/)
    {
      ($m, $d, $y) = ($1, $2, $3);
    }
    elsif ($iformat eq "british"
      && $val =~ /^(\d{1,2})\D(\d{1,2})\D(\d{2}|\d{4})$/)
    {
      ($d, $m, $y) = ($1, $2, $3);
    }
    else  # not a recognizable date; go to next value
    {
      next;
    }

    # convert 2-digit year to 4 digits on request
    $y += ($y >= $transition ? 1900 : 2000) if $add_century && $y < 100;

    warn "line $.: $val invalid?\n"
      if $warn && !is_valid_date ($y, $m, $d);

    if ($oformat eq "iso")
    {
      $val = sprintf ("$yearfmt-%02d-%02d", $y, $m, $d);
    }
    elsif ($oformat eq "us")
    {
      $val = sprintf ("%02d-%02d-$yearfmt", $m, $d, $y);
    }
    elsif ($oformat eq "british")
    {
      $val = sprintf ("%02d-%02d-$yearfmt", $d, $m, $y);
    }
    else
    {
      # should never happen!
      die "Logic error: unknown output format $oformat\n";
    }
    $val[$i] = $val;  # replace original value with new one
  }
  print join ("\t", @val) . "\n";
}
