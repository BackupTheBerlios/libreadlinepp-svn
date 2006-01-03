/*
 * libreadline++ -- libreadline++/history.cc
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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <libreadline++/util.hh>
#include <libreadline++/history.hh>

namespace rl {
/****************************************************************************/
History::History() throw()
    : _path(), _state(NULL)
{
    _init();
}
/****************************************************************************/
History::History(const std::string& path) throw()
    : _path(path), _state(NULL)
{
    _init();
}
/****************************************************************************/
History::~History() throw()
{
}
/****************************************************************************/
void
History::_init() throw()
{
    using_history();

    if (_path.empty())
    {
        const char * const homedir = std::getenv("HOME");
        if (homedir)
            _path.assign(std::string(homedir) + "/.history");
        else
            _path.assign(".history");
    }

    /// set state
    state();
}
/****************************************************************************/
void
History::read() throw (FileException)
{
    if (is_file(_path) and (read_history(_path.c_str()) != 0))
        throw FileException(_path);

    state();
}
/****************************************************************************/
void
History::read(int from, int to) throw (FileException)
{
    if (is_file(_path) and
        (read_history_range(_path.c_str(), from, to) != 0))
        throw FileException(_path);

    state();
}
/****************************************************************************/
void
History::write() throw (FileException)
{
    if (write_history(_path.c_str()) != 0)
        throw FileException(_path);
}
/****************************************************************************/
} // namespace rl

/* vim: set tw=80 sw=4 fdm=marker et : */
