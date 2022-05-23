#!/usr/bin/perl
# get_server_meta.pl

# Display server and connection metadata.

use strict;
use warnings;
use Cookbook;

my $dbh = Cookbook::connect ();

#@ _FRAG_
printf "hostinfo:   %s\n", $dbh->{hostinfo};
printf "protoinfo:  %s\n", $dbh->{protoinfo};
printf "serverinfo: %s\n", $dbh->{serverinfo};
printf "sock:       %s\n", $dbh->{sock};
printf "sockfd:     %s\n", $dbh->{sockfd};
printf "stats:      %s\n", $dbh->{stats};
printf "thread_id:  %s\n", $dbh->{thread_id};
#@ _FRAG_

$dbh->disconnect ();
