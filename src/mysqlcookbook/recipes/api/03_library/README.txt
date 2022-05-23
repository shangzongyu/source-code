This directory contains recipes relating to encapsulating the code
that establishes a connection to the MySQL server into a utility
routine in a library file. For each language, there is a library
file containing the connection routine, and a test harness file
that shows how to use that routine.  The harness file can be copied
as the basis for new programs.
- The harness files are in this directory.
- The library files are under the lib directory that's located at
  the top level of the recipes distribution.

The languages demonstrated are:

Java:
  Cookbook.java: library file that provides a Cookbook class with a
    connect() method.  Compile Cookbook.java to produce Cookbook.class
    and put Cookbook.class into a directory named com/kitebird/mcb (or
    com\kitebird\mcb under Windows) under a directory that is named
    in your CLASSPATH variable.

    The class contains two other methods, getErrorMessage() and
    printErrorMessage(), that can be used to obtain a message containing
    error information about a connection failure or to print the message
    to System.err.
  
    The class also contains a propsConnect() method (although this is not
    discussed until a later section of the chapter.  To use it, copy
    Cookbook.properties to the same location where you install
    Cookbook.class, and edit it to contain the appropriate connection
    parameters (MySQL username, password, hostname).
  Harness.java: program that uses the Cookbook class

PHP:
  Cookbook.php: module file
  harness.php: script that uses the module

Perl:
  Cookbook.pm: module file
  harness.pl: script that uses the module

Python:
  cookbook.py: module file
  harness.py: script that uses the module

Ruby:
  Cookbook.rb: module file
  harness.rb: script that uses the module

Go:
  Cookbook.go: module file
  harness.go: script that uses the module

