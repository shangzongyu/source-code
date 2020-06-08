# Makefile for Beginning Linux Programming 3rd Edition
# Chapter 4

ARGS=args argopt longopt
ENV=environ showenv
TIME=envtime gmtime ctime strftime
TMP=tmpnam
USER=user
HOST=hostget
LOG=syslog logmask
RES=limits

LDFLAGS=-lm

ALL= $(ARGS) $(ENV) $(TIME) $(TMP) $(USER) $(HOST) $(LOG) $(RES)

all: $(ALL)

clean:
	@rm -f $(ALL) *~
