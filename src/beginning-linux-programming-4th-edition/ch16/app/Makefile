all:  app

# If using Redhat 8+ or Fedora, may need to add -L/usr/lib/mysql to link to MySQL. 

app: app_mysql.c callbacks.c interface.c main.c app_gnome.h app_mysql.h
	gcc -o app -I/usr/include/mysql app_mysql.c callbacks.c interface.c main.c -L/usr/lib/mysql -lmysqlclient `pkg-config --cflags --libs libgnome-2.0 libgnomeui-2.0`

clean:
	rm -f app
