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

#include <iostream>
#include <cstdlib>
#include <libreadline++/readline.hh>

namespace rl {
/*** static members *********************************************************/
const ReadLine::EditMode ReadLine::vi    = static_cast<ReadLine::EditMode>(0);
const ReadLine::EditMode ReadLine::emacs = static_cast<ReadLine::EditMode>(1);
const ReadLine::State ReadLine::none = static_cast<ReadLine::State>(RL_STATE_NONE);
const ReadLine::State ReadLine::initializing = static_cast<ReadLine::State>(RL_STATE_INITIALIZING);
const ReadLine::State ReadLine::initialized = static_cast<ReadLine::State>(RL_STATE_INITIALIZED);
const ReadLine::State ReadLine::termprepped = static_cast<ReadLine::State>(RL_STATE_TERMPREPPED);
const ReadLine::State ReadLine::readcmd = static_cast<ReadLine::State>(RL_STATE_READCMD);
const ReadLine::State ReadLine::metanext = static_cast<ReadLine::State>(RL_STATE_METANEXT);
const ReadLine::State ReadLine::dispatching = static_cast<ReadLine::State>(RL_STATE_DISPATCHING);
const ReadLine::State ReadLine::moreinput = static_cast<ReadLine::State>(RL_STATE_MOREINPUT);
const ReadLine::State ReadLine::isearch = static_cast<ReadLine::State>(RL_STATE_ISEARCH);
const ReadLine::State ReadLine::nsearch = static_cast<ReadLine::State>(RL_STATE_NSEARCH);
const ReadLine::State ReadLine::search = static_cast<ReadLine::State>(RL_STATE_SEARCH);
const ReadLine::State ReadLine::numericarg = static_cast<ReadLine::State>(RL_STATE_NUMERICARG);
const ReadLine::State ReadLine::macroinput = static_cast<ReadLine::State>(RL_STATE_MACROINPUT);
const ReadLine::State ReadLine::macrodef = static_cast<ReadLine::State>(RL_STATE_MACRODEF);
const ReadLine::State ReadLine::overwrite = static_cast<ReadLine::State>(RL_STATE_OVERWRITE);
const ReadLine::State ReadLine::completing = static_cast<ReadLine::State>(RL_STATE_COMPLETING);
const ReadLine::State ReadLine::sighandler = static_cast<ReadLine::State>(RL_STATE_SIGHANDLER);
const ReadLine::State ReadLine::undoing = static_cast<ReadLine::State>(RL_STATE_UNDOING);
const ReadLine::State ReadLine::done = static_cast<ReadLine::State>(RL_STATE_DONE);
/****************************************************************************/
ReadLine::ReadLine(const std::string& name,
                   const std::string& prompt) throw()
    : _name(name), _prompt(prompt), _input(), _inithook(NULL)
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

    if (_inithook)
        rl_startup_hook = _inithook;
}
/****************************************************************************/
std::string&
ReadLine::operator()(void) const throw (ReadLineEOF)
{
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
