#!/usr/bin/perl
# uniq_name.pl: show how to use PID to create table name

use strict;
use warnings;

print "PID: $$\n";
#@ _GENERATE_NAME_WITH_PID_
my $tbl_name = "tmp_tbl_$$";
#@ _GENERATE_NAME_WITH_PID_
print "Table name: $tbl_name\n";
