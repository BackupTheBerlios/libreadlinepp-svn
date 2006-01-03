# $Id$

MAINTAINERCLEANFILES = Makefile.in *~ *.loT

cc_sources = \
	readline.cc \
	history.cc

hh_sources = \
	libreadline++.hh \
	exceptions.hh \
	readline.hh \
	history.hh

hh_sources_private = util.hh

lib_LTLIBRARIES = libreadline++.la
libreadline___la_SOURCES = $(hh_sources) $(hh_sources_private) $(cc_sources)
libreadline___la_LDFLAGS = -version-info $(LIBRARY_VERSION)
libreadline___la_LIBADD = @READLINE_LIBS@

library_includedir = $(includedir)/$(PACKAGE)
library_include_HEADERS = $(hh_sources)

EXTRA_DIST = doxygen.hh

srchtml: $(foreach f, $(libreadline___la_SOURCES), $(f).html)
	@for x in $(SUBDIRS) ; do \
		$(MAKE) -C $${x} $@ ; \
	done

%.cc.html: %.cc
	@echo Generating $@
	@test -d $(top_srcdir)/html/libreadline++ || \
		mkdir $(top_srcdir)/html/libreadline++
	@source-highlight -c ../src.css -s cpp -f html -t4 -n -i $? -o \
		../html/libreadline++/$@

%.hh.html: %.hh
	@echo Generating $@
	@test -d $(top_srcdir)/html/libreadline++ || \
		mkdir $(top_srcdir)/html/libreadline++
	@source-highlight -c ../src.css -s cpp -f html -t4 -n -i $? -o \
		../html/libreadline++/$@

