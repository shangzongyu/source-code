#!/usr/bin/perl
# transaction.pl: simple transaction demonstration

# By default, this creates an InnoDB table.  If you specify a storage
# engine on the command line, that will be used instead.  Normally,
# this should be a transaction-safe engine that is supported by your
# server.  However, you can pass a nontransactional storage engine
# to verify that rollback doesn't work properly for such engines.

# The script uses a table named "money" and drops it if necessary.
# Change the name if you have a valuable table with that name. :-)

use strict;
use warnings;
use Cookbook;

my $tbl_engine = (@ARGV ? shift (@ARGV) : "InnoDB");
print "Using storage engine $tbl_engine to test transactions\n";

my $dbh = Cookbook::connect ();

my $ref;

# Transaction handling using convenience functions to set up and clean up

print "----------\n";
print "This transaction should succeed.\n";
print "Table contents before transaction:\n";
init_table ($dbh, $tbl_engine);
display_table ($dbh);

#@ _TRANSACTION_MAIN_
$ref = transaction_init ($dbh);
eval
{
  # move some money from one person to the other
  $dbh->do ("UPDATE money SET amt = amt - 6 WHERE name = 'Eve'");
  $dbh->do ("UPDATE money SET amt = amt + 6 WHERE name = 'Ida'");
  # all statements succeeded; commit transaction
  $dbh->commit ();
};
transaction_finish ($dbh, $ref, $@);
#@ _TRANSACTION_MAIN_

print "Table contents after transaction:\n";
display_table ($dbh);

# Like previous example, but the transaction fails so that rollback
# can be demonstrated

print "----------\n";
print "This transaction should fail.\n";
print "Table contents before transaction:\n";
init_table ($dbh, $tbl_engine);
display_table ($dbh);

$ref = transaction_init ($dbh);
eval
{
  # move some money from one person to the other
  $dbh->do ("UPDATE money SET amt = amt - 6 WHERE name = 'Eve'");
  $dbh->do ("UPDATE money SET xamt = xamt + 6 WHERE name = 'Ida'");
  # all statements succeeded; commit transaction
  $dbh->commit ();
};
transaction_finish ($dbh, $ref, $@);

print "Table contents after transaction:\n";
display_table ($dbh);

$dbh->disconnect ();

# Create the example table and populate it with a couple of rows

sub init_table
{
my ($dbh, $tbl_engine) = @_;

  $dbh->{AutoCommit} = 1; # enable auto-commit
  $dbh->do ("DROP TABLE IF EXISTS money");
  $dbh->do ("CREATE TABLE money (name CHAR(5), amt INT, PRIMARY KEY(name)) ENGINE = $tbl_engine");
  $dbh->do ("INSERT INTO money (name, amt) VALUES('Eve', 10)");
  $dbh->do ("INSERT INTO money (name, amt) VALUES('Ida', 0)");
}

# Display the current contents of the example table

sub display_table
{
my $dbh = shift;

  my $sth = $dbh->prepare ("SELECT name, amt FROM money");
  $sth->execute ();
  while (my ($name, $amt) = $sth->fetchrow_array ())
  {
    print "$name has \$$amt\n";
  }
}

# Save a database handle's error and commit attributes, then set
# them to values appropriate for performing transactions.  Return the
# old attribute values in a hashref.

#@ _TRANSACTION_INIT_
sub transaction_init
{
my $dbh = shift;
my $attr_ref = {};  # create hash in which to save attributes

  $attr_ref->{RaiseError} = $dbh->{RaiseError};
  $attr_ref->{PrintError} = $dbh->{PrintError};
  $attr_ref->{AutoCommit} = $dbh->{AutoCommit};
  $dbh->{RaiseError} = 1; # raise exception if an error occurs
  $dbh->{PrintError} = 0; # don't print an error message
  $dbh->{AutoCommit} = 0; # disable auto-commit
  return $attr_ref;       # return attributes to caller
}
#@ _TRANSACTION_INIT_

# Roll back if the transaction failed.  Then restore the error-handling
# and auto-commit attributes.

#@ _TRANSACTION_FINISH_
sub transaction_finish
{
my ($dbh, $attr_ref, $error) = @_;

  if ($error) # an error occurred
  {
    print "Transaction failed, rolling back. Error was:\n$error\n";
    # roll back within eval to prevent rollback
    # failure from terminating the script
    eval { $dbh->rollback (); };
  }
  # restore error-handling and auto-commit attributes
  $dbh->{AutoCommit} = $attr_ref->{AutoCommit};
  $dbh->{PrintError} = $attr_ref->{PrintError};
  $dbh->{RaiseError} = $attr_ref->{RaiseError};
}
#@ _TRANSACTION_FINISH_
