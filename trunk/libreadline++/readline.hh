/*
 * libreadline++ -- libreadline++/readline.hh
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

#ifndef HAVE_LIBREADLINE___READLINE_HH
#define HAVE_LIBREADLINE___READLINE_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <string>
#include <exception>
#include <libreadline++/exceptions.hh>
#include <readline/readline.h>

namespace rl {

    /**
     * @class ReadLine readline.hh libreadline++/readline.hh
     * @brief Interface to readline's libreadline.
     * @todo Finish interface (currently very much incomplete).
     */

    class ReadLine
    {
        public:
            /** Default constructor.
             * @param name Application name (rl_readline_name) for conditional
             * parsing of inputrc.
             * @param prompt prompt text to use when displaying the prompt.
             */
            ReadLine(const std::string& name = "",
                     const std::string& prompt = "") throw();

            /** Constructor.
             * @param startup_hook function pointer to readline startup hook.
             */
            ReadLine(rl_hook_func_t *startup_hook) throw();

            /** Constructor.
             * @param name Application name (rl_readline_name) for conditional
             * parsing of inputrc.
             * @param prompt prompt text to use when displaying the prompt.
             * @param startup_hook function pointer to readline startup hook.
             */
            ReadLine(const std::string& name,
                     const std::string& prompt,
                     rl_hook_func_t *startup_hook) throw();

            /// Destructor.
            ~ReadLine() throw();

            /// Set name (rl_readline_name).
            inline void set_name(const std::string& name);
            /// Get name (rl_readline_name).
            inline const std::string& name() const { return _name; }
            /// Set prompt (rl_prompt).
            inline void set_prompt(const std::string& prompt)
            { _prompt.assign(prompt); }
            /// Get prompt (rl_prompt).
            inline const std::string& prompt() const { return _prompt; }
            
            /** Set attempted completion function
             * (rl_attempted_completion_function).
             */
            inline void set_attempted_comp_hook(rl_completion_func_t *hook);

            /// Set completion entry function (rl_completion_entry_function).
            inline void set_completion_entry_hook(rl_compentry_func_t *hook);

            /** Get user input.
             * @param text preexisting text to be present when the prompt is
             * shown (defaults to empty).
             * @returns reference to user input string.
             * @exception ReadLineEOF
             */
            std::string& operator()(const std::string& text = "") const
                throw (ReadLineEOF);

        private:
            void _init() throw();

            std::string _name;
            std::string _prompt;
            mutable std::string _input;
            rl_hook_func_t *_inithook;
    };

    inline void
    ReadLine::set_name(const std::string& name)
    {
        _name.assign(name);
        if (not _name.empty())
            rl_readline_name = _name.c_str();
    }

    inline void
    ReadLine::set_attempted_comp_hook(rl_completion_func_t *hook)
    {
        assert(hook);
        rl_attempted_completion_function = hook;
    }

    inline void
    ReadLine::set_completion_entry_hook(rl_compentry_func_t *hook)
    {
        assert(hook);
        rl_completion_entry_function = hook;
    }

} // namespace rl

#endif /* HAVE_LIBREADLINE___READLINE_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
