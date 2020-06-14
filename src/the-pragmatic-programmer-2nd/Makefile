DIRS=		c \
		cc \
		eiffel \
		java \
		lang \
		sh \
		perl 

SAVE_FILES = 	$(DIRS) Makefile README

all clean test::
		for i in $(DIRS) ;\
		do \
		  (cd $$i && [ -f Makefile ] && ( $(MAKE) $@ || exit 1)) || true;\
		done

clean::
		rm -f  *~ .filelist

reallyclean:	clean
		rm -rf examples.tgz examples.zip

.filelist:	clean
		( cd ..; \
		  rm -f examples/.filelist; \
		  for f in $(SAVE_FILES) ;\
		  do \
		    find examples/$$f -type f -print | \
                      grep -v CVS >> examples/.filelist; \
		  done \
		)

examples.tgz:	.filelist
		(cd .. && tar czfT examples/examples.tgz examples/.filelist)


examples.zip:	.filelist
		(cd .. && zip examples/examples.zip -@ <examples/.filelist)
