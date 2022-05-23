package Cookbook_Webutils;
# Cookbook_Utils.pm: MySQL Cookbook web-related utilities

require Exporter;
@ISA = qw(Exporter);
@EXPORT = qw(
  make_email_link
);

use strict;
use warnings;
use CGI qw(:standard escapeHTML);

# Create an email hyperlink from a name and email address

#@ _MAKE_EMAIL_LINK_
sub make_email_link
{
my ($name, $addr) = @_;

  $name = escapeHTML ($name);
  # return name as static text if address is undef or empty
  return $name if !defined ($addr) || $addr eq "";
  # return a hyperlink otherwise
  return a ({-href => "mailto:$addr"}, $name);
}
#@ _MAKE_EMAIL_LINK_

1;  # return true
