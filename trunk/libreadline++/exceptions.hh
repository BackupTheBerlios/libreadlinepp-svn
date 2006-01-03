/*
 * libreadline++ -- libreadline++/exceptions.hh
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

#ifndef HAVE_LIBREADLINE___EXCEPTIONS_HH
#define HAVE_LIBREADLINE___EXCEPTIONS_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file libreadline++/exceptions.hh
 * @brief Provides exception class definitions.
 */

#include <string>
#include <exception>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <libebt/libebt.hh>

namespace rl {

    /**
     * @class BaseException exceptions.hh libreadline++/exceptions.hh
     * @brief Base exception class.  All exception classes defined by
     * libreadline++ derive from this class.
     */

    class BaseException : public std::exception
    {
        protected:
            /// Destructor.
            virtual ~BaseException() throw() { }
    };

    /**
     * @class ErrnoException exceptions.hh libreadline++/exceptions.hh
     * @brief Exception class for errors where errno is set.
     */

    class ErrnoException : public BaseException
    {
        public:
            /// Default constructor.
            ErrnoException() throw();

            /** Constructor.
             * @param msg Error message prefix.
             */
            ErrnoException(const std::string& msg) throw()
                : _msg(msg), _code(errno) { }

            /// Destructor.
            virtual ~ErrnoException() throw() { }

            /// Get error message.
            virtual const char *what() const throw()
            {
                std::string error(std::strerror(_code));

                if (_msg.empty() and error.empty())
                    return "No error message.";

                if (_msg.empty())
                    return error.c_str();

                if (error.empty())
                    return _msg.c_str();

                return (_msg + ": " + error).c_str();
            }

        private:
            std::string _msg;
            int _code;
    };

    /**
     * @class FileException exceptions.hh libreadline++/exceptions.hh
     * @brief Exception for file-related errors.
     */

    class FileException : public ErrnoException
    {
        public:
            /// Default constructor.
            FileException() throw() { }

            /** Constructor.
             * @param msg Error message prefix.
             */
            FileException(const std::string& msg)
                : ErrnoException(msg) { }

            /// Destructor.
            virtual ~FileException() throw() { }
    };

    /**
     * @class BadCast exceptions.hh libreadline++/exeptions.hh
     * @brief Exception for failed type casts.
     */

    class BadCast : public BaseException
    {
        public:
            /// Default constructor.
            BadCast() throw() { }

            /** Constructor.
             * @param msg Error message.
             */
            BadCast(const std::string& msg) throw() : _msg(msg) { }

            /// Destructor.
            virtual ~BadCast() throw() { }

            /// Get error message
            virtual const char *what() const throw()
            { return _msg.c_str(); }

        private:
            std::string _msg;
    };

    /**
     * @class ReadLineEOF
     * @brief Readline EOF exception, thrown when ReadLine encounters an EOF.
     */

    class ReadLineEOF : public BaseException { };

} // namespace rl

#endif /* _HAVE_LIBREADLINE++_EXCEPTIONS_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
