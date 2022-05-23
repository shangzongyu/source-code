#!/usr/bin/perl
# connect2.pl: show other ways to connect to the MySQL server

# * Various ways to set connection attributes
# * How to specify a port number or Unix domain socket path explicitly.

use strict;
use warnings;
use DBI;

eval { # begin scope

# Set attributes to die on errors

my $dsn = "DBI:mysql:host=localhost;database=cookbook";
#@ _FRAG_DIE_ON_ERRORS_
my $dbh = DBI->connect ($dsn, "cbuser", "cbpass",
                        {PrintError => 0, RaiseError => 1});
#@ _FRAG_DIE_ON_ERRORS_

}; # end scope

print $@ if $@;

eval { # begin scope

# Set attributes to enable autocommit

my $dsn = "DBI:mysql:host=localhost;database=cookbook";
#@ _FRAG_AUTOCOMMIT_
my $dbh = DBI->connect ($dsn, "cbuser", "cbpass",
                        {PrintError => 0, RaiseError => 1, AutoCommit => 1});
#@ _FRAG_AUTOCOMMIT_

}; # end scope

print $@ if $@;

eval { # begin scope

# Set attributes using hashref

my $dsn = "DBI:mysql:host=localhost;database=cookbook";
#@ _FRAG_HASHREF_
my $conn_attrs = {PrintError => 0, RaiseError => 1, AutoCommit => 1};
my $dbh = DBI->connect ($dsn, "cbuser", "cbpass", $conn_attrs);
#@ _FRAG_HASHREF_

}; # end scope

print $@ if $@;

{ # begin scope

# Set the port explicitly

#@ _FRAG_PORT_
my $dsn = "DBI:mysql:host=127.0.0.1;database=cookbook;port=3307";
#@ _FRAG_PORT_
my $dbh = DBI->connect ($dsn, "cbuser", "cbpass");
if (!$dbh)
{
  warn "Cannot connect to server\n";
}
else
{
  print "Connected\n";
  $dbh->disconnect ();
  print "Disconnected\n";
}

} # end scope

{ # begin scope

# Set the socket file explicitly

#@ _FRAG_SOCKET_
my $dsn = "DBI:mysql:host=localhost;database=cookbook"
          . ";mysql_socket=/var/tmp/mysql.sock";
#@ _FRAG_SOCKET_
my $dbh = DBI->connect ($dsn, "cbuser", "cbpass");
if (!$dbh)
{
  warn "Cannot connect to server\n";
}
else
{
  print "Connected\n";
  $dbh->disconnect ();
  print "Disconnected\n";
}

} # end scope
