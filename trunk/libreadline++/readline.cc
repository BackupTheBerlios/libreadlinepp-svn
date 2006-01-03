/*
 * libreadline++ -- libreadline++/readline.cc
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

#include <cstdlib>
#include <libreadline++/readline.hh>

static const std::string * _rl_buf = NULL;

static int
default_readline_startup_hook()
{
    if (_rl_buf and not _rl_buf->empty())
        rl_insert_text(_rl_buf->c_str());
    return 0;
}

namespace rl {
/****************************************************************************/
ReadLine::ReadLine(const std::string& name,
                   const std::string& prompt) throw()
    : _name(name), _prompt(prompt), _input(),
      _inithook(default_readline_startup_hook)
{
    _init();
}
/****************************************************************************/
ReadLine::ReadLine(rl_hook_func_t *startup_hook) throw()
    : _name(), _prompt(), _input(), _inithook(startup_hook)
{
    _init();
}
/****************************************************************************/
ReadLine::ReadLine(const std::string& name,
                   const std::string& prompt,
                   rl_hook_func_t *startup_hook)
    throw()
    : _name(name), _prompt(prompt), _input(), _inithook(startup_hook)
{
    _init();
}
/****************************************************************************/
ReadLine::~ReadLine() throw()
{
}
/****************************************************************************/
void
ReadLine::_init() throw()
{
    if (not _name.empty())
        rl_readline_name = _name.c_str();

    rl_startup_hook = _inithook;
}
/****************************************************************************/
std::string&
ReadLine::operator()(const std::string& text) const throw (ReadLineEOF)
{
    _rl_buf = &text;
    _input.clear();

    char *input = readline(_prompt.c_str());
    if (not input)
        throw ReadLineEOF();

    if (*input)
        _input.assign(input);

    std::free(input);
    return _input;
}
/****************************************************************************/
} // namespace rl

/* vim: set tw=80 sw=4 fdm=marker et : */
