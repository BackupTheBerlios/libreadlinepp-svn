# $Id$

AUTOMAKE_OPTIONS = dejagnu

INCLUDES = -I$(top_builddir)
noinst_PROGRAMS = libreadline++
libreadline___SOURCES = libreadline++.cc
libreadline___LDADD = $(top_builddir)/libreadline++/libreadline++.la

EXTRA_DIST = libreadline++.tests config
CLEANFILES = *.sum *.log site.*
MAINTAINERCLEANFILES = Makefile.in *~ *.loT

RUNTESTDEFAULTFLAGS = --tool libreadline++ TEST=`pwd`/libreadline++ --srcdir $$srcdir
