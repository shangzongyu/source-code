#!/usr/bin/perl
#@ _PROLOG_1_
# yank_col.pl: Extract columns from input.

# Example: yank_col.pl --columns=2,11,5,9 filename

# Assumes tab-delimited, linefeed-terminated input lines.
#@ _PROLOG_1_

use strict;
use warnings;
use Getopt::Long;
$Getopt::Long::ignorecase = 0; # options are case sensitive

my $prog = "yank_col.pl";
my $usage = <<EOF;
Usage: $prog [options] [data_file]

Options:
--help
    Print this message
--columns=column-list
    Specify columns to extract, as a comma-separated list of column positions
EOF

my $help;
my $columns;

GetOptions (
  "help"      => \$help,      # print help message
  "columns=s" => \$columns    # specify column list
) or die "$usage\n";

die "$usage\n" if defined ($help);

my @col_list = split (/,/, $columns) if defined ($columns);
@col_list or die "$usage\n";      # nonempty column list is required

# make sure column specifiers are positive integers, and convert from
# 1-based to 0-based values

my @tmp;
for (my $i = 0; $i < @col_list; $i++)
{
  if ($col_list[$i] =~ /^\d+$/)             # single column number
  {
    die "Column specifier $col_list[$i] is not a positive integer\n"
      unless $col_list[$i] > 0;
    push (@tmp, $col_list[$i] - 1);
  }
  elsif ($col_list[$i] =~ /^(\d+)-(\d+)$/)  # column range m-n
  {
    my ($begin, $end) = ($1, $2);
    die "$col_list[$i] is not a valid column specifier\n"
      unless $begin > 0 && $end > 0 && $begin <= $end;
    while ($begin <= $end)
    {
      push (@tmp, $begin - 1);
      ++$begin;
    }
  }
  else
  {
    die "$col_list[$i] is not a valid column specifier\n";
  }
}
@col_list = @tmp;

#@ _INPUT_LOOP_
while (<>)            # read input
{
  chomp;
  my @val = split (/\t/, $_, 10000);  # split, preserving all fields
  # extract desired columns, mapping undef to empty string (can
  # occur if an index exceeds number of columns present in line)
  @val = map { defined ($_) ? $_ : "" } @val[@col_list];
  print join ("\t", @val) . "\n";
}
#@ _INPUT_LOOP_
