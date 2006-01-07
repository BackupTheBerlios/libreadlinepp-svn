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
            ///@{
            /// Denotes editing mode.
            enum EditMode {};
            static const EditMode emacs;
            static const EditMode vi;
            ///@}

            ///@{
            /// Denotes current state.
            enum State {};
            static const State none;
            static const State initializing;
            static const State initialized;
            static const State termprepped;
            static const State readcmd;
            static const State metanext;
            static const State dispatching;
            static const State moreinput;
            static const State isearch;
            static const State nsearch;
            static const State search;
            static const State numericarg;
            static const State macroinput;
            static const State macrodef;
            static const State overwrite;
            static const State completing;
            static const State sighandler;
            static const State undoing;
            static const State done;
            ///@}

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

            /// Get current edit mode.
            inline EditMode mode() const
            { return (rl_editing_mode ? emacs : vi ); }
            /// Set current edit mode.
            inline void set_mode(EditMode mode)
            { rl_editing_mode = mode; }

            /// Set the specified state bit.
            inline void set_state(State state) { RL_SETSTATE(state); }
            /// Unset the specified state bit.
            inline void unset_state(State state) { RL_UNSETSTATE(state); }
            /// Determine if the specified state bit is set.
            inline bool state_is_set(State state) const 
            { return RL_ISSTATE(state); }
            /// Get current state bits (rl_readline_state).
            inline int state() const { return rl_readline_state; }
            
            /** Set attempted completion function
             * (rl_attempted_completion_function).
             */
            inline void set_attempted_comp_hook(rl_completion_func_t *hook);
            /// Set completion entry function (rl_completion_entry_function).
            inline void set_completion_entry_hook(rl_compentry_func_t *hook);
            /// Set pre-input hook (rl_pre_input_hook).
            inline void set_pre_input_hook(rl_hook_func_t *hook);
            /// Set event hook (rl_event_hook).
            inline void set_event_hook(rl_hook_func_t *hook);
            /// Set getc function (rl_getc_function).
            inline void set_getc_function(rl_getc_func_t *func);

            /** Get user input.
             * @returns reference to user input string.
             * @exception ReadLineEOF
             */
            std::string& operator()(void) const throw (ReadLineEOF);

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

    inline void
    ReadLine::set_pre_input_hook(rl_hook_func_t *hook)
    {
        assert(hook);
        rl_pre_input_hook = hook;
    }

    inline void
    ReadLine::set_event_hook(rl_hook_func_t *hook)
    {
        assert(hook);
        rl_event_hook = hook;
    }

    inline void
    ReadLine::set_getc_function(rl_getc_func_t *func)
    {
        assert(func);
        rl_getc_function = func;
    }

} // namespace rl

#endif /* HAVE_LIBREADLINE___READLINE_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
