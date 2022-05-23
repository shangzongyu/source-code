#!/usr/bin/perl
# get_server_version.pl: get server version string and number from server

# This script demonstrates how to get the string by issuing a
# SELECT VERSION() statement.  Another way (which is actually more
# efficient, because no statement is needed) is to access the
# $dbh->{mysql_serverinfo} database handle attribute.

use strict;
use warnings;
use Cookbook;

# Return a list consisting of the server version number in both string
# and numeric forms.  Return undef on an error.

#@ _GET_SERVER_VERSION_
sub get_server_version
{
my $dbh = shift;
my ($ver_str, $ver_num);
my ($major, $minor, $patch);

  # fetch result into scalar string
  $ver_str = $dbh->selectrow_array ("SELECT VERSION()");
  return undef unless defined ($ver_str);
  ($major, $minor, $patch) = split (/\./, $ver_str);
  $patch =~ s/\D.*$//; # strip nonnumeric suffix if present
  $ver_num = $major*10000 + $minor*100 + $patch;
  return ($ver_str, $ver_num);
}
#@ _GET_SERVER_VERSION_

#@ _REQUIRE_SERVER_VERSION_
# Return true or false depending on whether the server version is at
# or above the given version.  $version should be specified using digits
# only, e.g., 32307 for 3.23.7.

# This function assumes that the minor and patch version parts are < 100.

sub require_server_version
{
my ($dbh, $required_version) = @_;
my ($version, $major, $minor, $patch);

  $version = $dbh->selectrow_array ("SELECT VERSION()");
  return 0 unless defined ($version); # fail if can't get version
  ($major, $minor, $patch) = split (/\./, $version);
  $patch =~ s/-.*//;  # strip suffix
  $version = $major*10000 + $minor*100 + $patch;
  return $version >= $required_version;
}
#@ _REQUIRE_SERVER_VERSION_

my $dbh = Cookbook::connect ();

{ # begin scope

# get server version string and number and print them
#@ _GET_BOTH_
my ($ver_str, $ver_num) = get_server_version ($dbh);
#@ _GET_BOTH_
print "Version: $ver_str ($ver_num)\n";

} # end scope

{ # begin scope

# try the forms that get just one element of the returned list
#@ _GET_STR_ONLY_
my $ver_str = (get_server_version ($dbh))[0]; # string form
#@ _GET_STR_ONLY_
#@ _GET_NUM_ONLY_
my $ver_num = (get_server_version ($dbh))[1]; # numeric form
#@ _GET_NUM_ONLY_
print "Version: $ver_str ($ver_num)\n";

} # end scope

{ # begin scope

# Test for some particular features
#@ _TEST_FUNCTIONS_
my $ver_num = (get_server_version ($dbh))[1];
printf "Event scheduler:    %s\n", ($ver_num >= 50106 ? "yes" : "no");
printf "4-byte Unicode:     %s\n", ($ver_num >= 50503 ? "yes" : "no");
printf "Fractional seconds: %s\n", ($ver_num >= 50604 ? "yes" : "no");
printf "SHA-256 passwords:  %s\n", ($ver_num >= 50606 ? "yes" : "no");
printf "ALTER USER:         %s\n", ($ver_num >= 50607 ? "yes" : "no");
printf "INSERT DELAYED:     %s\n", ($ver_num >= 50700 ? "no" : "yes");
#@ _TEST_FUNCTIONS_

} # end scope

$dbh->disconnect ();
