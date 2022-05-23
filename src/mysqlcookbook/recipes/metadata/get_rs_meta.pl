#!/usr/bin/perl
# get_rs_meta.pl: run a statement and display its result set metadata

# The program runs a default statement, which can be overridden by supplying
# a statement as an argument on the command line.

use strict;
use warnings;
use Cookbook;

#@ _DEFAULT_STATEMENT_
my $stmt = "SELECT name, birth FROM profile";
#@ _DEFAULT_STATEMENT_
# override statement with command line argument if one was given
$stmt = shift (@ARGV) if @ARGV;

my $dbh = Cookbook::connect ();

# Run a statement that generates a result set and display the available
# metadata.
# Metadata information is valid after execute() and before end of
# result set is reached.
# Number of columns is in NUM_OF_FIELDS statement handle attribute.

#@ _DISPLAY_METADATA_
printf "Statement: %s\n", $stmt;
my $sth = $dbh->prepare ($stmt);
$sth->execute();
# metadata information becomes available at this point ...
printf "NUM_OF_FIELDS: %d\n", $sth->{NUM_OF_FIELDS};
print "Note: statement has no result set\n" if $sth->{NUM_OF_FIELDS} == 0;
for my $i (0 .. $sth->{NUM_OF_FIELDS}-1)
{
  printf "--- Column %d (%s) ---\n", $i, $sth->{NAME}->[$i];
  printf "NAME_lc:          %s\n", $sth->{NAME_lc}->[$i];
  printf "NAME_uc:          %s\n", $sth->{NAME_uc}->[$i];
  printf "NULLABLE:         %s\n", $sth->{NULLABLE}->[$i];
  printf "PRECISION:        %d\n", $sth->{PRECISION}->[$i];
  printf "SCALE:            %d\n", $sth->{SCALE}->[$i];
  printf "TYPE:             %d\n", $sth->{TYPE}->[$i];
  printf "mysql_is_blob:    %s\n", $sth->{mysql_is_blob}->[$i];
  printf "mysql_is_key:     %s\n", $sth->{mysql_is_key}->[$i];
  printf "mysql_is_num:     %s\n", $sth->{mysql_is_num}->[$i];
  printf "mysql_is_pri_key: %s\n", $sth->{mysql_is_pri_key}->[$i];
  printf "mysql_max_length: %d\n", $sth->{mysql_max_length}->[$i];
  printf "mysql_table:      %s\n", $sth->{mysql_table}->[$i];
  printf "mysql_type:       %d\n", $sth->{mysql_type}->[$i];
  printf "mysql_type_name:  %s\n", $sth->{mysql_type_name}->[$i];
}
$sth->finish ();  # release result set because we didn't fetch its rows
#@ _DISPLAY_METADATA_

$dbh->disconnect ();
