#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.50)
AC_INIT(wavedump, 3.5.3, support.computing@caen.it)
AC_CONFIG_AUX_DIR([src])
AM_INIT_AUTOMAKE(wavedump, 3.5.3)
AC_CONFIG_SRCDIR([inc/WaveDump.h])
#AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_DEFINE(LINUX,[1],"Define LINUX")
# Checks for libraries.
AC_CHECK_HEADER(CAENDigitizer.h,[a=0],[a=1])
AC_CHECK_HEADER(CAENDigitizerType.h,[a=0],[a=1])
AC_CHECK_LIB(CAENDigitizer,CAEN_DGTZ_OpenDigitizer,[a=0], [a=1])
if test $a == 1; then
        AC_MSG_ERROR([
                CAENDigitizer must be installed on your system.])
fi

AC_CHECK_PROG(GNUPLOT,gnuplot,"ok","no")
if test $GNUPLOT == "no"; then
        AC_MSG_WARN(
	*****************************************************************
		    GnuPLot not fount WaveDump will be unable to show graphical data.
		    *****************************************************************
	)
fi

AC_MSG_WARN
# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([malloc.h stdint.h stdlib.h string.h sys/time.h sys/timeb.h termios.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_HEADER_TIME

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_SELECT_ARGTYPES
AC_CHECK_FUNCS([atexit gettimeofday memset pow select strstr])
AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_CHECK_PROG(HAVE_GNUPLOT, gnuplot, yes, no)
if test "x$HAVE_GNUPLOT" = "xno"; then
	AC_MSG_ERROR([*** Gnuplot not found])
fi
AC_OUTPUT
