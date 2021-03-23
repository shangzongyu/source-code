.PHONY: clean all

OBJDIR=./build
OBJS=$(OBJDIR)/greeting.html $(OBJDIR)/greeting.js
TSC=./node_modules/.bin/tsc

all: $(OBJS)

$(OBJDIR)/greeting.html: src/greeting.html
	cp src/greeting.html $(OBJDIR)/greeting.html

$(OBJDIR)/greeting.js: src/greeting.ts
	$(TSC)

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf ./build
