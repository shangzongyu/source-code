This directory contains demonstration programs that go along with
the instructions in the companion document "Executing Programs from
the Command Line" that illustrate how to run programs from the
command line.

That document is available at:  https://github.com/svetasmirnova/mysqlcookbook/blob/master/cmdline.md

perldemo.pl, rubydemo.pl, phpdemo.php,and pythondemo.py have no
shebang (#!) line that names the appropriate language processor,
and they do not have the +x access mode enabled.  You need to execute
them as an argument to the language processor:

perl perldemo.pl
ruby rubydemo.rb
php phpdemo.php
python pythondemo.py

perldemo2.pl, rubydemo2.pl, and pythondemo2.py have a shebang line
and (on Unix) have the +x access mode enabled. On Unix, you should be able
to execute them directly like this:

./perldemo2.pl
./rubydemo2.rb
./pythondemo2.py

On Windows, if you have filename associations set up for Python, Ruby, and
Python, you should be able to execute them directly like this:

perldemo2.pl
rubydemo2.rb
pythondemo2.py
