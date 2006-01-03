# Process this file with autoconf to produce a configure script.
# $Id: configure.ac 246 2005-04-26 12:03:53Z ka0ttic $

AC_PREREQ(2.59)
AC_INIT(libreadline++, [0.1.0], [ka0ttic@gentoo.org])
AC_CONFIG_SRCDIR([libreadline++/readline.cc])
AC_CONFIG_AUX_DIR(config)

# release versioning
VERSION_MAJOR=0
VERSION_MINOR=1
VERSION_MICRO=0
VERSION_SUFFIX=
VERSION_SUFFIX_VERSION=
VERSION_FULL="$VERSION_MAJOR.$VERSION_MINOR.$VERSION_MICRO"

if ! test -z "$VERSION_SUFFIX" ; then
    VERSION_FULL="$VERSION_FULL"_"$VERSION_SUFFIX""$VERSION_SUFFIX_VERSION"
fi

VERSION="$VERSION_FULL"

AC_SUBST(VERSION_MAJOR)
AC_SUBST(VERSION_MINOR)
AC_SUBST(VERSION_MICRO)
AC_SUBST(VERSION_SUFFIX)
AC_SUBST(VERSION_SUFFIX_VERSION)
AC_SUBST(VERSION_FULL)

# shared lib versioning
LIBRARY_VERSION=1:0:0
#               | | |
#        +------+ | +---+
#        |        |     |
#        current:revision:age
#        |        |     |
#        |        |     +- increment if interfaces have been added
#        |        |        set to zero if interfaces have been removed
#                          or changed
#        |        +- increment if source code has changed
#        |           set to zero if current is incremented
#        +- increment if interfaces have been added, removed or changed
AC_SUBST(LIBRARY_VERSION)

AM_INIT_AUTOMAKE(libreadline++, [$VERSION_FULL])

dnl --enable-debug
AC_MSG_CHECKING([whether to enable debugging code/flags])
AC_ARG_ENABLE(debug,
    AC_HELP_STRING([--enable-debug],[Enable debugging code/flags]),
    [enable_debug=$enableval],[enable_debug=no])
AC_MSG_RESULT([$enable_debug])
AM_CONDITIONAL(DEBUG, test x$enable_debug != "xno")

AC_LANG([C++])
AC_PROG_CXX
AC_PROG_MAKE_SET
AC_PROG_INSTALL

#dnl hack to disable damn f77 libtool checks (stolen from sandbox's configure.in)
m4_undefine([AC_PROG_F77])
m4_defun([AC_PROG_F77],[])
AC_PROG_LIBTOOL

LIBTOOL="${LIBTOOL} --silent"
AC_SUBST(LIBTOOL)

#dnl SED is defined by the LT_AC_PROG_SED ran by AC_PROG_LIBTOOL
AC_SUBST(SED)

LRL_CHECK_CXXFLAG([-pedantic])
LRL_CHECK_CXXFLAG([-ansi])
LRL_CHECK_CXXFLAG([-W])
LRL_CHECK_CXXFLAG([-Wextra])
LRL_CHECK_CXXFLAG([-Wall])
LRL_CHECK_CXXFLAG([-Wold-style-cast])
LRL_CHECK_CXXFLAG([-Woverloaded-virtual])
LRL_CHECK_CXXFLAG([-Wredundant-decls])

if test x$enable_debug != "xno" ; then
    LRL_CHECK_CXXFLAG([-ggdb3])
    AC_DEFINE(DEBUG, 1, [Enable debugging code])
fi

dnl Required functions

dnl Required headers

dnl Required libraries
AC_CHECK_HEADERS(readline/readline.h,,
    [AC_MSG_ERROR([readline/readline.h was not found])])
AC_CHECK_LIB(readline, readline,[READLINE_LIBS="-lreadline"],
    [AC_MSG_ERROR([libreadline was not found])])
AC_CHECK_HEADERS(readline/history.h,,
    [AC_MSG_ERROR([readline/history.h was not found])])
AC_CHECK_LIB(history, add_history,[READLINE_LIBS="$READLINE_LIBS -lhistory"],
    [AC_MSG_ERROR([libhistory was not found])])
AC_SUBST(READLINE_LIBS)

AM_CONFIG_HEADER(config.h)
AC_OUTPUT(Makefile
	  doc/Makefile
          doc/Doxyfile
	  libreadline++/Makefile
	  examples/Makefile)
