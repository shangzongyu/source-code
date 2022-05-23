#!/usr/bin/python3
# rand_test2.py: create a frequency distribution of RAND() values.
# This provides a test of the randomness of RAND().

import cookbook

conn = cookbook.connect()

nchoices = 10   # how many different numbers to permit
npicks = 1000   # number of times to pick a number

# drop and recreate the t table, then populate it

cursor = conn.cursor()
cursor.execute("DROP TABLE IF EXISTS t")
cursor.execute("CREATE TABLE t (num INT, counter INT)")

# populate the table with rows numbered 1 through nchoices, each
# initialized with a counter value of zero

for i in range(1, nchoices+1):
  cursor.execute("INSERT INTO t (num,counter) VALUES(%s,0)", (i,))
conn.commit()

# Now run a zillion picks and count how many times each item gets picked

for i in range(0, npicks):
  cursor.execute("SELECT num FROM t ORDER BY RAND() LIMIT 1")
  row = cursor.fetchone()
  # update count for selected value
  cursor.execute("UPDATE t SET counter = counter + 1 WHERE num = %s", (row[0],))
conn.commit()

# Print the resulting frequency distribution

cursor.execute("SELECT num, counter FROM t ORDER BY num")
for (num, counter) in cursor:
  print("%2d  %d" % (num, counter))

# Display total number of choices and standard deviation of distribution

cursor.execute("SELECT SUM(counter), STD(counter) FROM t")
(n, stddev) = cursor.fetchone()
print("total number of selections: %d" % n)
print("standard deviation of selections: %f" % stddev)

cursor.close()

conn.close()
