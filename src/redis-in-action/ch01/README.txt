
To run all of the code listings, you must have the following installed for
your platform:

1. Redis 2.6.x (or a release candidate if 2.6 is not out officially yet)
   If you are using an older version than 2.6, some of the commands we use
   may not work right, or may not be available - http://redis.io/download
2. Python 2.6.x or Python 2.7.x - http://python.org
3. A version of the Redis Python libraries with a version number >= your Redis
   version number - http://pypi.python.org/pypi/redis/

Full installation instructions are available in appendix A.

For most of our code listings, you can simply navigate a terminal to the path
where you extracted our code, and run 'python <name of file>'. For example,
when running 'python ch01_listing_source.py' from the proper path, I see:

--------------------------------------------------------------------------------
We posted a new article with id: 1

Its HASH looks like:
{'poster': 'username', 'votes': '1', 'title': 'A title', 'link': 'http://www.goo
gle.com', 'time': '1347539969.24'}

We voted for the article, it now has votes: 2

The currently highest-scoring articles are:
[{'id': 'article:1',
  'link': 'http://www.google.com',
  'poster': 'username',
  'time': '1347539969.24',
  'title': 'A title',
  'votes': '2'}]

We added the article to a new group, other articles include:
[{'id': 'article:1',
  'link': 'http://www.google.com',
  'poster': 'username',
  'time': '1347539969.24',
  'title': 'A title',
  'votes': '2'}]

Done!
.
----------------------------------------------------------------------
Ran 1 test in 0.080s

OK
--------------------------------------------------------------------------------

Running other modules should result in similar results, specific to whatever
module was run. Python's unittest framework was used for the runner for the
sake of convenience, but our use is *not* typical of standard testing
procedures for Python. The code used for "testing" is meant as an example of
how to use the code that we've written, not as an example of how to write
tests with Python.

Some chapter source listings do not have any tests, as they do not have any
listings with Python functions shown.
