/*
 * libreadline++ -- libreadline++/util.hh
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
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * libreadline++; if not, write to the Free Software Foundation, Inc., 59
 * Temple Place, Suite 325, Boston, MA  02111-1257  USA
 */

#ifndef HAVE_LIBREADLINE___UTIL_HH
#define HAVE_LIBREADLINE___UTIL_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file libreadline++/util.hh
 * @brief Provides some general purpose utility classes/functions.
 */

#include <string>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libreadline++/exceptions.hh>

namespace rl {

    /**                              
     * Is the given path a regular file?
     * @param path Path.           
     * @returns A boolean value.
     */
               
    inline bool
    is_file(const std::string& path) throw()
    {                 
        struct stat s;
        return ((stat(path.c_str(), &s) == 0) ? S_ISREG(s.st_mode) : false);
    }

    /**
     * Convert a type to a std::string.
     * @param v Value of type T.
     * @returns A std::string object.
     */
        
    template <typename T>
    inline std::string
    stringify(const T& v)
    {
        std::ostringstream os;
        os << v;
        return os.str();
    }

    /**                                                                         
     * Convert a std::string to a type.
     * @param s A std::string object.
     * @returns Value of type T.
     */
        
    template <typename T>
    inline T
    destringify(const std::string& s) throw (BadCast)
    {
        std::istringstream is(s.c_str());
    
        T v;                         
        is >> v;
    
        if (not is.eof())
            throw BadCast("Failed to cast '"+s+"'.");
    
        return v;
    }

} // namespace rl

#endif /* HAVE_LIBREADLINE___UTIL_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
