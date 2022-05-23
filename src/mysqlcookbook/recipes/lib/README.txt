The files in this directory are library files that contain utility routines
intended to be shared by multiple scripts.

On my system, I create a directory named /usr/local/lib/mcb and install
the library files there.

The Java files are in the package com.kitebird.mcb, so compile them
to produce .class file and install them under this directory:
   /usr/local/lib/mcb/com/kitebird/mcb
The *.properties file can be installed there, too.

To enable scripts that need these libraries to find them, you can
set the appropriate environment or configuration variables for your
language processors.  For example (tcsh syntax):

setenv PERLLIB /usr/local/lib/mcb
setenv RUBYLIB /usr/local/lib/mcb
setenv PYTHONPATH /usr/local/lib/mcb

For PHP, modify the include_path variable in php.ini.
For Java, add the appropriate library classes to CLASSPATH.
