#!/usr/bin/perl
# get_connection_meta.pl: get connection metadata

use strict;
use warnings;
use Cookbook;

my $dbh = Cookbook::connect ();

{ # begin scope

#@ _CURRENT_DATABASE_
my $db = $dbh->selectrow_array ("SELECT DATABASE()");
printf "Default database: %s\n", ($db ne "" ? $db : "(no database selected)");
#@ _CURRENT_DATABASE_

} # end scope

{ # begin scope

#@ _GREETING_
my ($user, $host) = $dbh->selectrow_array (q{
                            SELECT SUBSTRING_INDEX(USER(),'@',1),
                                SUBSTRING_INDEX(USER(),'@',-1)
                        });
print "Hello, $user!  Good to see you.\n";
print "I see you're connecting from $host.\n" unless $host eq "";
#@ _GREETING_

} # end scope

{ # begin scope

#@ _SPLIT_IN_API_WITH_PATTERN_
my ($user, $host) = ($dbh->selectrow_array (
                            "SELECT USER()") =~ /([^@]+)@?(.*)/);
#@ _SPLIT_IN_API_WITH_PATTERN_
print "$user, $host\n";

} # end scope

{ # begin scope

#@ _SPLIT_IN_API_WITH_SPLIT_
my ($user, $host) = split (/@/, $dbh->selectrow_array ("SELECT USER()"));
#@ _SPLIT_IN_API_WITH_SPLIT_
print "$user, $host\n";

} # end scope

$dbh->disconnect ();
