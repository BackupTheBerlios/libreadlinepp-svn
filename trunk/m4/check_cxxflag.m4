AC_DEFUN([LRL_CHECK_CXXFLAG], [
	  lrl_save_CXXFLAGS=$CXXFLAGS
	  CXXFLAGS="$CXXFLAGS $1"
	  AC_MSG_CHECKING([if $CXX supports the $1 flag])
	  AC_COMPILE_IFELSE([
#include <string>
std::string s;
	],
	[lrl_cxxflag_success=yes],
	[lrl_cxxflag_success=no])
	AC_MSG_RESULT($lrl_cxxflag_success)
	CXXFLAGS="$lrl_save_CXXFLAGS"
	if test "x$lrl_cxxflag_success" = "xyes" ; then
		CXXFLAGS="$CXXFLAGS $1"
	fi
	])

