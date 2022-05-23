#!/usr/bin/perl
# guess_table.pl: Characterize the contents of a data file and use the
# information to guess a CREATE TABLE statement for the file.

# Usage: guess_table.pl table_name data_file

# To do:
# - Use value range information for something.  It's collected but not yet
#   used.  For example, suggest better INT types.
# - Get rid of nonnegative attribute; it can be assessed now from the range.

# Load a data file and read column names and data values.
# Guess the declaration for each of the columns based on what the data
# values look like, then generate an SQL CREATE TABLE statement for the
# table.  Because the column declarations are just guesses, you'll likely
# want to edit the output, for example, to change a data type or
# length.  You may also want to add indexes.  Nevertheless, using this
# script can be easier than writing the CREATE TABLE statement by hand.

# Some assumptions:
# - Lines are tab-delimited, linefeed-terminated
# - Dates consist of 3 numeric parts, separated by - or /, in y/m/d order

# Here are some ways that guess_table.pl could be improved.  Each of
# them would make it smarter, albeit at the cost of increased processing
# requirements. Some of the suggestions are likely impractical for really
# huge files.

# - For numeric columns, use min/max values to better guess the type.
# - Keep track of the number of unique values in a column.  If there
#   aren't many, the column might be a good candidate for being an ENUM.
#   Testing should not be case sensitive, because ENUM columns are not
#   case sensitive.
# - Make the date guessing code smarter.  Have it recognize non-ISO format
#   and attempt to make suggestions that a column needs to be reformatted.
#   (This actually needs to see entire column, because that would help
#   it distinguish US from British formats WRT order of month and day.)
#   This would need to track min/max for each of the three date parts.
# - If all values in a column are unique, suggest that it should be a PRIMARY
#   KEY or a UNIQUE index.
# - For DATETIME columns, permit some times to be missing without flagging
#   column as neither DATE nor TIME.

# Paul DuBois
# paul@kitebird.com
# 2002-01-31

# Sveta Smirnova
# 2022-01-29

# 2002-01-31
# - Created.
# 2002-02-19
# - Add code to track ranges for numeric columns and for the three date
#   subparts of columns that look like they contain dates.
# 2002-02-20
# - Added --lower and --upper options to force column labels to lowercase
#   or uppercase.
# 2002-03-01
# - For character columns longer than 255 characters, choose TEXT type based
#   on maximum length.
# 2002-04-04
# - Add --quote-names option to quote table and column names `like this`.
#   The resulting statement requires MySQL 3.23.6 or higher.
# 2002-07-16
# - Fix "uninitialized value" warnings resulting from missing columns in
#   data lines.
# - Don't attempt to assess date characteristics for columns that are always
#   empty.
# 2005-12-28
# - Make --quote-names the default, add --skip-quote-names option so that
#   identifier quoting can be turned off.
# - Default data type now is VARCHAR, not CHAR.
# 2006-06-10
# - Emit UNSIGNED for double/decimal columns if they're unsigned.
# 2022-01-29
# - Removed UNSIGNED for double/decimal columns because 
#   this keyword is deprecated for these types in MySQL 8.0

use strict;
use warnings;
use Getopt::Long;
$Getopt::Long::ignorecase = 0; # options are case sensitive
$Getopt::Long::bundling = 1;   # permit short options to be bundled

# ----------------------------------------------------------------------

# Create information structures to use for characterizing each column in
# in the data file.  We need to know whether any nonnumeric values are
# found, whether numeric values are always integers, and the maximum length
# of column values.

# Argument is the array of column labels.
# Creates an array of hash references and returns a reference to that array.

sub init_col_info
{
my @labels = @_;
my @col_info;

  for my $i (0 .. @labels - 1)
  {
    my $info = {};
    $info->{label} = $labels[$i];
    $info->{max_length} = 0;

    # these can be tested directly, so they're set false until found
    # to be true
    $info->{hasempty} = 0;    # has empty values
    $info->{hasnonempty} = 0; # has nonempty values

    # these can be assessed only by seeing all the values in the
    # column, so they're set true until discovered by counterexample
    # to be false
    $info->{numeric} = 1;     # used to detect general numeric types
    $info->{integer} = 1;     # used to detect INT
    $info->{nonnegative} = 1; # used to detect UNSIGNED
    $info->{temporal} = 1;    # used to detect general temporal types
    $info->{date} = 1;        # used to detect DATE
    $info->{datetime} = 1;    # used to detect DATETIME
    $info->{time} = 1;        # used to detect TIME

    # track min/max value for numeric columns
    $info->{min_val} = undef;
    $info->{max_val} = undef;

    # track min/max for each of three date parts
    $info->{date_range} = [ undef, undef, undef];

    push (@col_info, $info);
  }
  return \@col_info;
}

sub print_create_table
{
my ($tbl_name, $col_info_list, $quote_names) = @_;
my $ncols = @{$col_info_list};
my $s;
my $extra = "";

  for my $i (0 .. $ncols - 1)
  {
    my $info = $col_info_list->[$i];

    $s .= ",\n" if $i > 0;
    $s .= $extra if $extra ne "";
    $extra = "";

    $info->{label} = quote_identifier ($info->{label}) if $quote_names;
    $s .= "  $info->{label} ";

    if (!$info->{hasnonempty})  # column is always empty, make wild guess
    {
      $s .= "CHAR(10)    /* NOTE: column is always empty */";
      next;
    }

    # if the column has nonempty values but one of
    # these hasn't been ruled out, that's a problem
    if ($info->{numeric} && $info->{temporal})
    {
      die "Logic error: $info->{label} was characterized as both"
          . " numeric and temporal\n";
    }

    if ($info->{numeric})
    {
      if ($info->{integer})
      {
        $s .= "BIGINT";
        $s .= " UNSIGNED" if $info->{nonnegative};
# TODO: use range to make guess about type
# Print "might be YEAR" if in range...(0, 1901-2155)
      }
      else
      {
        $s .= "DOUBLE";
      }
    }
    elsif ($info->{temporal})
    {
      # if a date column looks more like a US or British
      # date, add some comments to that effect
      if (exists ($info->{date_type}))
      {
        my $ref = $info->{date_type};
        $extra .= "  # $info->{label} might be a US date\n"
                  if $ref->{us};
        $extra .= "  # $info->{label} might be a British date\n"
                  if $ref->{br};
      }
      if ($info->{date})
      {
        $s .= "DATE";
      }
      elsif ($info->{datetime})
      {
        $s .= "DATETIME";
      }
      elsif ($info->{time})
      {
        $s .= "TIME";
      }
      else
      {
        die "Logic error: $info->{label} is flagged as temporal, but"
            . " not as any of the temporal types\n";
      }
    }
    else
    {
      if ($info->{max_length} < 256)
      {
        $s .= "VARCHAR($info->{max_length})";
      }
      elsif ($info->{max_length} < 65536)
      {
        $s .= "TEXT";
      }
      elsif ($info->{max_length} < 16777216)
      {
        $s .= "MEDIUMTEXT";
      }
      else
      {
        $s .= "LONGTEXT";
      }
    }
    # if a column doesn't have empty values, guess that it cannot be NULL
    $s .= " " . ($info->{hasempty} ? "NULL" : "NOT NULL");
  }

  $tbl_name = quote_identifier ($tbl_name) if $quote_names;
  $s = "CREATE TABLE $tbl_name\n(\n$s\n);\n";
  print $s;
}

sub print_report
{
my $col_info_list = shift;
my $ncols = @{$col_info_list};
my $s;

  for my $i (0 .. $ncols - 1)
  {
    my $info = $col_info_list->[$i];

    printf "Column %d: %s\n", $i+1, $info->{label};
    if (!$info->{hasnonempty})  # column is always empty
    {
      print " column is always empty\n";
      next;
    }

    # if the column has nonempty values but one of
    # these hasn't been ruled out, that's a problem
    if ($info->{numeric} && $info->{temporal})
    {
      die "Logic error: $info->{label} was characterized as both"
          . " numeric and temporal\n";
    }

    print " column has empty values: "
          . ($info->{hasempty} ? "yes" : "no") . "\n";
    printf " column value maximum length = %d\n", $info->{max_length};

    if ($info->{numeric})
    {
      printf " column is numeric (range: %g - %g)\n",
             $info->{min_val}, $info->{max_val};
      if ($info->{integer})
      {
        print " column is integer\n";
        if ($info->{nonnegative})
        {
          print " column is nonnegative\n";
        }
      }
    }
    elsif ($info->{temporal})
    {
      if ($info->{date})
      {
        my $ref = $info->{date_range};
        print " column contains date values";
        printf " (part ranges: %d - %d, %d - %d, %d - %d)\n",
               $ref->[0]->{min}, $ref->[0]->{max},
               $ref->[1]->{min}, $ref->[1]->{max},
               $ref->[2]->{min}, $ref->[2]->{max};
        $ref = $info->{date_type};
        printf " most likely date types: ISO: %s; US: %s; British: %s\n",
               ($ref->{iso} ? "yes" : "no"),
               ($ref->{us} ? "yes" : "no"),
               ($ref->{br} ? "yes" : "no");
      }
      elsif ($info->{datetime})
      {
        my $ref = $info->{date_range};
        print " column contains date+time values";
        printf " (part ranges: %d - %d, %d - %d, %d - %d)\n",
               $ref->[0]->{min}, $ref->[0]->{max},
               $ref->[1]->{min}, $ref->[1]->{max},
               $ref->[2]->{min}, $ref->[2]->{max};
        $ref = $info->{date_type};
        printf " most likely date types: ISO: %s; US: %s; British: %s\n",
               ($ref->{iso} ? "yes" : "no"),
               ($ref->{us} ? "yes" : "no"),
               ($ref->{br} ? "yes" : "no");
      }
      elsif ($info->{time})
      {
        print " column contains time values\n";
      }
      else
      {
        die "Logic error: $info->{label} is flagged as temporal, but"
            . " not as any of the temporal types\n";
      }
    }
    else
    {
      print " column appears to be a string"
            . " (cannot further narrow the type)\n";
    }
  }
}

# Quote an identifier by doubling internal backticks
# and adding surrounding backticks

sub quote_identifier
{
my $ident = shift;

  $ident =~ s/`/``/g;
  return '`' . $ident . '`';

}

# ----------------------------------------------------------------------

my $prog = "guess_table.pl";
my $usage = <<EOF;
Usage: $prog [options] [data_file]

Options:
--help
    Print this message
--labels, -l
    Interpret first input line as row of table column labels
    (default = c1, c2, ...)
--lower, --upper
    Force column labels to be in lowercase or uppercase
--quote-names, --skip-quote-names
   Quote or do not quote table and column identifiers with `` characters
   in case they are reserved words (default = quote identifiers)
--report , -r
    Report mode; print findings rather than generating a CREATE
    TABLE statement
--table=tbl_name, -t tbl_name
    Specify table name (default = t)
EOF

my $help;
my $labels;     # expect a line of column labels?
my $tbl_name = "t"; # table name (default: t)
my $report;
my $lower;
my $upper;
my $quote_names = 1;
my $skip_quote_names;

GetOptions (
  # =s means a string value is required after the option
  "help"              => \$help,            # print help message
  "labels|l"          => \$labels,          # expect row of column labels
  "table|t=s"         => \$tbl_name,        # table name
  "report|r"          => \$report,          # report mode
  "lower"             => \$lower,           # lowercase labels
  "upper"             => \$upper,           # uppercase labels
  "quote-names"       => \$quote_names,     # quote identifiers
  "skip-quote-names"  => \$skip_quote_names # don't quote identifiers
) or die "$usage\n";

die "$usage\n" if defined ($help);

$report = defined ($report);  # convert defined/undefined to boolean
$lower = defined ($lower);
$upper = defined ($upper);
$quote_names = defined ($quote_names);
$quote_names = 0 if defined ($skip_quote_names);

die "--lower and --upper were both specified; that makes no sense\n"
                        if $lower && $upper;

my $line;
my $line_count = 0;
my @labels;   # column labels
my $ncols;    # number of columns
my $col_info_list;

# If labels are expected, read the first line to get them
if ($labels)
{
  defined ($line = <>) or die;
  chomp ($line);
  @labels = split (/\t/, $line);
}

# Arrays to hold line numbers of lines with too many/too few fields.
# The first line in the file is assumed to be representative.  The
# number of fields it contains becomes the norm against which any following
# lines are assessed.

my @excess_fields;
my @too_few_fields;

while (<>)
{
  chomp ($line = $_);
  ++$line_count;
  if (!defined ($ncols))  # don't know this until first data line read
  {
    # determine number of columns (assume no more than 10,000)
    my @val = split (/\t/, $line, 10000);
    $ncols = @val;
    if (@labels)  # label count must match data column count
    {
      die "Label count doesn't match data column count\n"
                    if $ncols != @labels;
    }
    else      # if there were no labels, create them
    {
      @labels = map { "c" . $_ } 1 .. $ncols;
    }
    $col_info_list = init_col_info (@labels);
  }

  my @val = split (/\t/, $line, 10000);
  push (@excess_fields, $line_count) if @val > $ncols;
  push (@too_few_fields, $line_count) if @val < $ncols;
  for my $i (0 .. $ncols - 1)
  {
    my $val = ($i < @val ? $val[$i] : "");  # use "" if field is missing
    my $info = $col_info_list->[$i];

    $info->{max_length} = length ($val)
      if $info->{max_length} < length ($val);

    if ($val eq "")
    {
      # column does have empty values
      $info->{hasempty} = 1;
      next; # no other tests apply
    }
    $info->{hasnonempty} = 1;

    # perform numeric tests if no nonnumeric values have yet been seen

    if ($info->{numeric})
    {
      # numeric test (doesn't recognize scientific notation)
      if ($val =~ /^[-+]?(\d+(\.\d*)?|\.\d+)$/)
      {
        # not int if contains decimal point
        $info->{integer} = 0 if $val =~ /\./;
        # not unsigned if begins with minus sign
        $info->{nonnegative} = 0 if $val =~ /^-/;

        # track min/max value
        $info->{min_val} = $val
          if !defined ($info->{min_val}) || $info->{min_val} > $val;
        $info->{max_val} = $val
          if !defined ($info->{max_val}) || $info->{max_val} < $val;
      }
      else
      {
        # column contains nonnumeric information
        $info->{numeric} = 0;
        $info->{integer} = 0;
      }
    }

    # perform temporal tests if no nontemporal values have yet been seen

    if ($info->{temporal})
    {
      # date/datetime test
      # permit date, date hour:min, date hour:min:sec
      if (($info->{date} || $info->{datetime})
        && $val =~ /^(\d+)[-\/](\d+)[-\/](\d+)\s*(\d+:\d+(:\d+)?)?$/)
      {
        # it's not a time
        $info->{time} = 0;

        # not a date if time part was present; not a
        # datetime if no time part was present
        $info->{ defined ($4) ? "date" : "datetime" } = 0;

        # use the first three parts to track range of date parts
        my @val = ($1, $2, $3);
        my $ref = $info->{date_range};
        foreach my $i (0 .. 2)
        {
          # if this is the first value we've checked, create the
          # structure to hold the min and max; otherwise compare
          # the stored min/max to the current value
          if (!defined ($ref->[$i]))
          {
            $ref->[$i]->{min} = $val[$i];
            $ref->[$i]->{max} = $val[$i];
            next;
          }
          $ref->[$i]->{min} = $val[$i]
            if $ref->[$i]->{min} > $val[$i];
          $ref->[$i]->{max} = $val[$i]
            if $ref->[$i]->{max} < $val[$i];
        }
      }
      # time test
      # permit hour:min, hour:min:sec
      elsif ($info->{time} && $val =~ /^\d+:\d+(:\d+)?$/)
      {
        # it's not a date or datetime
        $info->{date} = 0;
        $info->{datetime} = 0;
      }
      else
      {
        # column contains nontemporal information
        $info->{temporal} = 0;
      }
    }
  }
}

die "Input contained no data lines\n" if $line_count == 0;
die "Input lines all were empty\n" if $ncols == 0;

# Look at columns that look like DATE or DATETIME columns and attempt
# to determine whether they appear to be in ISO, US, or British format.
# (Skip columns that are always empty, because these assessments cannot
# be made for such columns.)

for my $i (0 .. $ncols - 1)
{
  my $info = $col_info_list->[$i];
  next unless $info->{hasnonempty};
  next unless $info->{temporal} && ($info->{date} || $info->{datetime});
  my $ref = $info->{date_range};
  # assume that the column is valid as each of the types until ruled out
  my $valid_as_iso = 1; # [CC]YY-MM-DD
  my $valid_as_us = 1;  # MM-DD-[CC]YY
  my $valid_as_br = 1;  # DD-MM-[CC]YY
  # first segment is US month, British day
  my $min = $ref->[0]->{min};
  my $max = $ref->[0]->{max};
  $valid_as_us = 0 if $min < 0 || $max > 12;
  $valid_as_br = 0 if $min < 0 || $max > 31;
  # second segment is US day, British month, ISO month
  $min = $ref->[1]->{min};
  $max = $ref->[1]->{max};
  $valid_as_us = 0 if $min < 0 || $max > 31;
  $valid_as_br = 0 if $min < 0 || $max > 12;
  $valid_as_iso = 0 if $min < 0 || $max > 12;
  # third segment is ISO day
  $min = $ref->[2]->{min};
  $max = $ref->[2]->{max};
  $valid_as_iso = 0 if $min < 0 || $max > 31;
  if (!$valid_as_iso && !$valid_as_us && !$valid_as_br)
  {
    $info->{temporal} = 0;  # huh! guess it's not a date after all
  }
  else    # save date type results for later
  {
    $info->{date_type}->{iso} = $valid_as_iso;
    $info->{date_type}->{us} = $valid_as_us;
    $info->{date_type}->{br} = $valid_as_br;
  }
}


warn "# Number of lines = $line_count, columns = $ncols\n";
warn "# Number of lines with too few fields: " . scalar (@too_few_fields) . "\n"
                            if @too_few_fields;
warn "# Number of lines with excess fields: " . scalar (@excess_fields) . "\n"
                            if @excess_fields;

if ($report)
{
  print_report ($col_info_list);
}
else
{
  for my $i (0 .. $ncols - 1)
  {
    my $info = $col_info_list->[$i];
    $info->{label} = lc ($info->{label}) if $lower;
    $info->{label} = uc ($info->{label}) if $upper;
  }
  print_create_table ($tbl_name, $col_info_list, $quote_names);
}
