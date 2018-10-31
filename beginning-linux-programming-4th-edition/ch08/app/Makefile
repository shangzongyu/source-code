all:  app

app: app_mysql.c app_test.c app_mysql.h
	gcc -g -o app -I/usr/include/mysql app_mysql.c app_test.c -lmysqlclient -L/usr/lib/mysql


