/*
 * libreadline++ -- libreadline++/libreadline++.hh
 * $Id$
 * Copyright (c) 2005 Aaron Walker <ka0ttic@gentoo.org>
 *
 * This file is part of libreadline++.
 *
 * libreadline++ is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * libreadline++ is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * libreadline++; if not, write to the Free Software Foundation, Inc., 59
 * Temple Place, Suite 325, Boston, MA  02111-1257  USA
 */

#ifndef HAVE_LIBREADLINE___LIBREADLINE___HH
#define HAVE_LIBREADLINE___LIBREADLINE___HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file libreadline++/libreadline++.hh
 * @brief Convenience include header with doxygen main page documentation.
 */

#include <libreadline++/exceptions.hh>
#include <libreadline++/readline.hh>
#include <libreadline++/history.hh>

///@{
/// Common defines.
#ifndef LIBREADLINEPP_DEPRECATED
# if defined(__GNUC__) || defined(DOXYGEN)
#   define LIBREADLINEPP_DEPRECATED __attribute__ ((deprecated))
# else
#   define LIBREADLINEPP_DEPRECATED
# endif
#endif

#ifndef LIBREADLINEPP_UNUSED
# if defined(__GNUC__) || defined(DOXYGEN)
#   define LIBREADLINEPP_UNUSED __attribute__ ((unused))
# else
#   define LIBREADLINEPP_UNUSED
# endif
#endif
///@}

/**
 * @mainpage libreadline++ API Documentation
 *
 * @section overview Overview
 *
 * The libreadline++ library provides C++ interfaces for GNU readline's
 * libreadline and libhistory libraries.
 *
 * @section usage Usage
 *
 * Below is a simple example of using the libreadline++ library:
 *
 * @include calc/main.cc
 *
 * @section compiling Compiling libreadline++
 *
 * libreadline++ uses GNU autotools for configuration/building.  Building and
 * installing is as easy as:
 *
 * @verbatim
./configure
make
sudo make install
@endverbatim

 * Besides a standard C++ library, the only requirement is the
 * <a href="http://cnswww.cns.cwru.edu/php/chet/readline/rltop.html">GNU readline</a>
 * package.
 */

/**                                                                             
 * @page Authors Authors                                                        
 * @section Authors Authors                                                     
 *                                                                              
 * libreadline++ was written by Aaron Walker <ka0ttic@gentoo.org>.
 */
                            
/**                                                 
 * @page ChangeLog ChangeLog
 * @section ChangeLog ChangeLog
 * @verbinclude ChangeLog
 */                       
                                                         
/**
 * @page License License                                         
 * @section License License                                          
 * @verbinclude COPYING        
 */

/**
 * @namespace rl
 * @brief Main namespace all of libreadline++ resides in.
 */

#endif /* HAVE_LIBREADLINE___LIBREADLINE___HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
