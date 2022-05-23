#!/usr/bin/perl

# Show how to get row and column counts for $dbh-callable select methods

# Note: You may get "undefined value" warnings if $DBI::err or $DBI::errstr
# are undef (which is a legal "no-error" value).

use strict;
use warnings;
use Cookbook;

@ARGV == 1 or die "You must specify the statement as this program's argument\n";
my $stmt = $ARGV[0];

my $dbh = Cookbook::connect ();

print "Statement: $stmt\n";

{ # begin scope

my @val = $dbh->selectrow_array ($stmt);
#@ _SELECTROW_ARRAY_
my $ncols = @val;
my $nrows = $ncols ? 1 : 0;
#@ _SELECTROW_ARRAY_
print "selectrow_array:    nrows = $nrows, ncols = $ncols\n";

} # end scope

{ # begin scope

#@ _SELECTROW_ARRAYREF_
my $ref = $dbh->selectrow_arrayref ($stmt);
my $ncols = defined ($ref) ? @{$ref} : 0;
my $nrows = $ncols ? 1 : 0;
#@ _SELECTROW_ARRAYREF_
print "selectrow_arrayref: nrows = $nrows, ncols = $ncols\n";
print "values: @{$ref}\n";

} # end scope

{ # begin scope

#@ _SELECTROW_HASHREF_
my $ref = $dbh->selectrow_hashref ($stmt);
my $ncols = defined ($ref) ? keys (%{$ref}) : 0;
my $nrows = $ncols ? 1 : 0;
#@ _SELECTROW_HASHREF_
print "selectrow_hashref:  nrows = $nrows, ncols = $ncols\n";

} # end scope

{ # begin scope

#@ _SELECTCOL_ARRAYREF_
my $ref = $dbh->selectcol_arrayref ($stmt);
my $nrows = defined ($ref) ? @{$ref} : 0;
my $ncols = $nrows ? 1 : 0;
#@ _SELECTCOL_ARRAYREF_
print "selectcol_arrayref: nrows = $nrows, ncols = $ncols\n";
if (defined ($ref))
{
  print "values:\n";
  for my $i (0 .. @{$ref} - 1)
  {
    print "$i: $ref->[$i]\n";
  }
}

} # end scope

{ # begin scope

#@ _SELECTALL_ARRAYREF_
my $ref = $dbh->selectall_arrayref ($stmt);
my $nrows = defined ($ref) ? @{$ref} : 0;
my $ncols = $nrows ? @{$ref->[0]} : 0;
#@ _SELECTALL_ARRAYREF_
print "selectall_arrayref: nrows = $nrows, ncols = $ncols\n";
if (defined ($ref))
{
  print "values:\n";
  for my $i (0 .. @{$ref} - 1)
  {
    my $row_ref = $ref->[$i];
    print "row $i: @{$row_ref}\n";
  }
}

} # end scope

{ # begin scope

# this example uses a hardwired statement, because it's necessary to specify
# a key field to call it, and it's difficult to know what that might be
# for some arbitrary statement.

# This example WILL NOT WORK for DBI prior to 1.20.  selectall_hashref()
# is not present at all before DBI 1.16, and has a different behavior
# than it currently does for version 1.16 - 1.19.

my $stmt = "SELECT * FROM profile";

#@ _SELECTALL_HASHREF_1_
my $ref = $dbh->selectall_hashref ("SELECT * FROM profile", "id");
#@ _SELECTALL_HASHREF_1_
#@ _SELECTALL_HASHREF_2_
my @keys = defined ($ref) ? keys (%{$ref}) : ();
my $nrows = scalar (@keys);
my $ncols = $nrows ? keys (%{$ref->{$keys[0]}}) : 0;
#@ _SELECTALL_HASHREF_2_
print "Statement for selectall_hashref: $stmt\n";
print "selectall_hashref:  nrows = $nrows, ncols = $ncols\n";
if (defined ($ref))
{
  print "values:\n";
  for my $key (sort (@keys))
  {
    my $row_ref = $ref->{$key};
    print "row $key: ";
    foreach my $key (keys (%{$row_ref}))
    {
      $row_ref->{$key} = "NULL" unless defined ($row_ref->{$key});
      print " $key=$row_ref->{$key}";
    }
    print "\n";
  }
}

} # end scope

{ # begin scope

#@ _SELECTALL_PLACEHOLDER_
my $ref = $dbh->selectall_arrayref (
  "SELECT name, birth, foods FROM profile WHERE id > ? AND color = ?",
  undef, 3, "green"
);
#@ _SELECTALL_PLACEHOLDER_
if (defined ($ref))
{
  print "selectall_arrayref (placeholder):\n";
  for my $i (0 .. @{$ref} - 1)
  {
    my $row_ref = $ref->[$i];
    print "row $i: @{$row_ref}\n";
  }
}

} # end scope

# Test some of the error-handling behavior

print "Check error-handling behavior\n";

my $val;
my @val;

$dbh->{RaiseError} = 0;
$dbh->{PrintError} = 1;

# This statement is illegal

$stmt = "SELECT";

@val = $dbh->selectrow_array ($stmt);
print "\@val is empty\n" unless @val;
print "\@val is not empty: @val\n" if @val;
print "errstr: $DBI::errstr, error: $DBI::err\n";

$val = $dbh->selectrow_array ($stmt);
print "\$val is undef\n" unless defined ($val);
print "\$val is not undef: $val\n" if defined ($val);
print "errstr: $DBI::errstr, error: $DBI::err\n";

# This statement is legal, but returns an empty result set; thus the
# return value cannot be distinguished from an error

$stmt = "SELECT 1 FROM profile WHERE 1 = 0";

@val = $dbh->selectrow_array ($stmt);
print "\@val is empty\n" unless @val;
print "\@val is not empty: @val\n" if @val;
print "errstr: $DBI::errstr, error: $DBI::err\n";

$val = $dbh->selectrow_array ($stmt);
print "\$val is undef\n" unless defined ($val);
print "\$val is not undef: $val\n" if defined ($val);
print "errstr: $DBI::errstr, error: $DBI::err\n";

# This statement is legal, but returns a result set consisting of a single
# NULL.  The scalar return value cannot be distinguished from an empty
# result set or an error.

$stmt = "SELECT NULL FROM profile WHERE 1 = 1";

@val = $dbh->selectrow_array ($stmt);
print "\@val is empty\n" unless @val;
print "\@val is not empty: @val\n" if @val;
print "errstr: $DBI::errstr, error: $DBI::err\n";

$val = $dbh->selectrow_array ($stmt);
print "\$val is undef\n" unless defined ($val);
print "\$val is not undef: $val\n" if defined ($val);
print "errstr: $DBI::errstr, error: $DBI::err\n";

$dbh->{RaiseError} = 1;
$dbh->{PrintError} = 0;

$dbh->disconnect ();
