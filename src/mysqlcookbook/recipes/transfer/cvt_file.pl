#!/usr/bin/perl
# cvt_file.pl: Convert data file formats.

# This serves as a general-purpose data formatter.  For example, it can
# read and write data in CSV, merge, or tab-delimited format.  It can be
# used, for example, to convert CSV input to tab-delimited format for
# programs that understand only tab-delimited data.

# Reads named files or stdin.

# Doesn't map ^K (such as is used by FileMaker to signify repeated values
# within a field) to anything.

# Paul DuBois
# paul@kitebird.com
# 2000-12-12

# 2000-12-12
# - Created.
# 2002-03-09
# - Fix bug with binary attribute not being passed to Text::CSV_XS->new().
# - Redo input mechanism to work around Text::CSV_XS input separator problem.
# 2003-05-02
# - Fix bug help message display bug.

use strict;
use warnings;
use IO::Handle;
use Text::CSV_XS;
use Getopt::Long;
$Getopt::Long::ignorecase = 0; # options are case sensitive
$Getopt::Long::bundling = 1;   # permit short options to be bundled

my $prog = "cvt_file.pl";
my $usage = <<EOF;
Usage: $prog [ options ] [ data_file ]

Options:
--help
    Print this message
--format=format_name
--iformat=format_name, --if=format_name
--oformat=format_name, --of=format_name
    Set format for input/output, input only, or output only
--delim=c
--idelim=c
--odelim=c
    Set column delimiter for input/output, input only, or output only
--quote=c
--iquote=c
--oquote=c
    Set column quote character for input/output, input only, or output only
--eol=c
--ieol=c
--oeol=c
    Set end-of-line marker for input/output, input only, or output only
--labels, -l
    Read row of column labels from input, write row of labels to output
--ilabels
    Expect to read row of column labels from input
--olabels
    Write a row of column labels to input

The format arguments are shorthand for specifying common delimiter and
quote combinations:
    tab - tab-delimited, no quotes
    csv - Comma Separated Values format (comma-delimited, quoted as necessary)

For the delimiter, quote, and eol values, you can use certain
special sequences:
    0xhh, 0Xhh - character specified as hex value
    \\n, \\r, \\t, \\0, \\\\ - tab, linefeed, carriage return, NUL, backslash
For example, --oeol=0x0d0a signifies carriage return/newline for output.

Other arguments:
data_file
    Name of data file to convert
EOF

my $help;

# default file format parameters - all unset
my %ioattrs = (
  format => undef, labels => undef,
  sep_char => undef, quote_char => undef, eol => undef
);
my %iattrs = (
  format => undef, labels => undef,
  sep_char => undef, quote_char => undef, eol => undef
);
my %oattrs = (
  format => undef, labels => undef,
  sep_char => undef, quote_char => undef, eol => undef
);

GetOptions (
  # =s means a string value is required after the option
  "help"      => \$help,                # print help message
  "format=s"  => \$ioattrs{format},     # set input/output format
  "if=s"      => \$iattrs{format},      # set input format only
  "iformat=s" => \$iattrs{format},      # ditto
  "of=s"      => \$oattrs{format},      # set output format only
  "oformat=s" => \$oattrs{format},      # ditto
  "labels|l"  => \$ioattrs{labels},     # read/write row of column labels
  "ilabels"   => \$iattrs{labels},      # expect to read row of column labels
  "il"        => \$iattrs{labels},      # expect to read row of column labels
  "olabels"   => \$oattrs{labels},      # write row of column labels
  "ol"        => \$oattrs{labels},      # write row of column labels
  "delim=s"   => \$ioattrs{sep_char},   # set input/output delimiter
  "idelim=s"  => \$iattrs{sep_char},    # set input delimiter only
  "odelim=s"  => \$oattrs{sep_char},    # set output delimiter only
  "quote=s"   => \$ioattrs{quote_char}, # set input/output quote char
  "iquote=s"  => \$iattrs{quote_char},  # set input quote char only
  "oquote=s"  => \$oattrs{quote_char},  # set output quote char only
  "eol=s"     => \$ioattrs{eol},        # set input/output eol
  "ieol=s"    => \$iattrs{eol},         # set input eol only
  "oeol=s"    => \$oattrs{eol}          # set output eol only
) or die "$usage\n";

die "$usage\n" if defined ($help);

# for any input- or output-specific parameter that isn't set, override it
# with the corresponding overall parameter, if the latter is set
foreach my $param ("format", "labels", "sep_char", "quote_char", "eol")
{
  $iattrs{$param} = $ioattrs{$param} if !defined ($iattrs{$param});
  $oattrs{$param} = $ioattrs{$param} if !defined ($oattrs{$param});
}

# Set up input and output attribute hashes. Then create from them new hashes
# containing only those # attributes that have meaning for Text::CSV_XS->new().

setup_attrs (\%iattrs);
setup_attrs (\%oattrs);
my %icsvattrs;
my %ocsvattrs;
foreach my $param ("sep_char", "quote_char", "eol", "escape_char", "binary")
{
  $icsvattrs{$param} = $iattrs{$param};
  $ocsvattrs{$param} = $oattrs{$param};
}
my $icsv = Text::CSV_XS->new (\%icsvattrs);
my $ocsv = Text::CSV_XS->new (\%ocsvattrs);

# We must open each file explicitly (not use @ARGV as a continuous stream)
# because if --ilabels was specified the first line of each file must be
# interpreted as a row of column labels.

if (@ARGV == 0)       # read stdin
{
  read_file (\%iattrs, \%oattrs, $icsv, $ocsv);
}
else
{
  foreach my $file (@ARGV)
  {
    open (STDIN, $file) or die "cannot open $file: $!\n";
    read_file (\%iattrs, \%oattrs, $icsv, $ocsv);
    # if labels in output were requested, print them only
    # prior to *first* file
    $oattrs{labels} = 0;
  }
}

# ----------------------------------------------------------------------

# Interpret a string that may contain special sequences:
# 0xhh, 0Xhh - char specified as hex value
# \n, \r, \t, \0, \\ - tab, linefeed, carriage return, NUL, backslash

sub interpret_option
{
my $s_in = shift;
my $s_out;
my %escmap = (      # map escape sequences to characters
  "n"   => "\n",
  "r"   => "\r",
  "t"   => "\t",
  "0"   => "\0",
  "\\"  => "\\"
);

  return undef unless defined ($s_in);
  while ($s_in ne "")
  {
    if ($s_in =~ /^0x/i)          # hex value
    {
      $s_out .= pack ("H2", substr ($s_in, 2, 2));
      $s_in = substr ($s_in, 4);
    }
    elsif (substr ($s_in, 0, 1) eq "\\")  # escape sequence
    {
      my $c = substr ($s_in, 1, 1);
      # use char mapping, or char itself if not in map
      $s_out .= (exists ($escmap{$c}) ? $escmap{$c} : $c);
      $s_in = substr ($s_in, 2);
    }
    else                  # literal char
    {
      $s_out .= substr ($s_in, 0, 1);
      $s_in = substr ($s_in, 1);
    }
  }
  return $s_out;
}

# Set up file processing attributes for CSV object creation.
# Argument is a reference to a hash containing command-line argument
# settings.  These are mapped from the form permitted on the command line
# to the form required for the Text::CSV_XS new() method.

# Defaults for sep_char and quote_char are determined by
# the format.  However, if values for these were set explicitly on the
# command line, don't use the default.

# Turn on binary mode because read/write calls may fail if lines contain
# ^K or other junk.

sub setup_attrs
{
my $ref = shift;

  $ref->{binary} = 1;       # force binary mode on

  # convert defined/undefined state into true/false
  $ref->{labels} = defined ($ref->{labels});

  # interpret special chars in the file structure options
  $ref->{sep_char} = interpret_option ($ref->{sep_char});
  $ref->{quote_char} = interpret_option ($ref->{quote_char});
  $ref->{eol} = interpret_option ($ref->{eol});

  $ref->{eol} = "\n" if !defined ($ref->{eol});   # default line-ending

  $ref->{format} = "tab" if !defined ($ref->{format});  # default format
  if ($ref->{format} eq "csv")
  {
    $ref->{sep_char} = "," if !defined ($ref->{sep_char});
    $ref->{quote_char} = '"' if !defined ($ref->{quote_char});
  }
  elsif ($ref->{format} eq "tab") # tab-delimited format
  {
    $ref->{sep_char} = "\t" if !defined ($ref->{sep_char});
    # default for quote_char is undef here; no need to set it
  }
  else
  {
    die "Unknown format: $ref->{format}\n";
  }

  # make the escape char same as quote char to cause instances of the
  # quote char in data values to be doubled
  $ref->{escape_char} = $ref->{quote_char};
}

# Read data file, which is assumed to be open on STDIN.  Write to STDOUT.
# Text::CSV_XS understands only \n or \r\n for input line separators, so
# instead of using its getline() method, use the IO::Handle's getline()
# method directly to read input.

sub read_file
{
my ($iattrs, $oattrs, $icsv, $ocsv) = @_;
my @val;
my $in = new IO::Handle;
my $out = new IO::Handle;
my @labels;
my $labels_written = 0;
my $line_count = 0;

  $in->fdopen (fileno (STDIN), "r") or die "Cannot fdopen STDIN: $!\n";
  $out->fdopen (fileno (STDOUT), "w") or die "Cannot fdopen STDOUT: $!\n";

  IO::Handle->input_record_separator ($iattrs->{eol});
  if ($iattrs->{labels})          # read column labels
  {
    ++$line_count;
    my $s = $in->getline ();
    chomp ($s);
    $icsv->parse ($s)
      or die "read error on line $line_count:" . $icsv->error_input ();
    @labels = $icsv->fields ();
  }
  while (!$in->eof ())
  {
    ++$line_count;
    my $s = $in->getline ();
    chomp ($s);
    $icsv->parse ($s)
      or die "read error on line $line_count:" . $icsv->error_input ();
    @val = $icsv->fields ();

    # write the output line, preceded by labels if they were requested
    # (make up some labels if the input didn't contain any)
    if ($oattrs->{labels} && $labels_written == 0)  # need labels
    {
      if (!@labels)   # if labels weren't present, make them up
      {
        # construct array of consecutive numbers, prefix each with
        # a letter
        @labels = map { "c" . $_ } 1 .. scalar (@val);
      }
      $ocsv->print ($out, \@labels);
      $labels_written = 1;
    }
    $ocsv->print ($out, \@val) or die "print() error\n";
  }
  undef $in;      # release file handles
  undef $out;
}
