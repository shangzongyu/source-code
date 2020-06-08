# Makefile for Beginning Linux Programming 3rd Edition
# Chapter 15

CLIENTS=client1 client2 client3
SERVERS=server1 server2 server3 server4 server5
INFO=getname getdate getdate-udp
SELECT=select

CFLAGS=-g
LDFLAGS=-g

ALL= $(CLIENTS) $(SERVERS) $(INFO) $(SELECT)

all: $(ALL)

clean:
	@rm -f $(ALL) *~ *.o
