/*
 * libreadline++ -- libreadline++/history.hh
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

#ifndef HAVE_LIBREADLINE___HISTORY_HH
#define HAVE_LIBREADLINE___HISTORY_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

/**
 * @file libreadline++/history.hh
 * @brief Provides the History class definition.
 */

#include <string>
#include <cstdlib>
#include <libreadline++/exceptions.hh>
#include <readline/history.h>

namespace rl {

    ///@{
    /// typedefs for naming consistency
    typedef HIST_ENTRY HistoryEntry;
    typedef HIST_ENTRY ** HistoryList;
    typedef HISTORY_STATE HistoryState;
    typedef histdata_t HistoryData;
    ///@}

    /**
     * @class History history.hh libreadline++/history.hh
     * @brief Interface to readline's libhistory.
     */

    class History
    {
        public:
            typedef std::size_t size_type;

            /// Default constructor.
            History() throw();

            /* Constructor.
             * @param path path to history file.
             */
            History(const std::string& path) throw();

            /// Destructor.
            ~History() throw();

            /// Get path to history file.
            inline const std::string& path() const;

            /// Set path to history file.
            inline void set_path(const std::string& path);

            /// Add line to history.
            inline void add(const std::string& line);
            
            /** Remove line from history.
             * @param offset offset of entry to remove.
             * @returns removed history entry.
             */
            inline HistoryEntry *remove(int offset);

            /// Free history entry.
            inline HistoryData free(HistoryEntry *entry);

            /// Replace history entry.
            inline HistoryEntry *replace(int offset, const std::string& line,
                    HistoryData data);

            /// Get offset of current HistoryElement.
            inline int offset() const;

            /// Set current history offset.
            inline bool set_offset(int offset);

            /// Get current history entry.
            inline HistoryEntry *current_entry() const;

            /// Get history entry at the specified offset.
            inline HistoryEntry *entry_at_offset(int offset) const;

            /// Clear history.
            inline void clear();

            /// Is the history stifled?
            inline bool is_stifled() const;

            /** Stifle history.
             * @param max maximum number of entries to remember.
             */
            inline void stifle(int max);

            /** Unstifle history.
             * @returns previously-set maximum number of history entries (or a
             * negative value if history was not previously stifled).
             */
            inline int unstifle();

            /** Get current history state.
             * @returns a pointer to a HistoryState object.
             */
            inline HistoryState *state() const;

            /** Set history state.
             * @param state pointer to a HistoryState object.
             */
            inline void set_state(HistoryState *state);

            /** Read history from disk.
             * @exception FileException
             */
            void read() throw (FileException);

            /** Read history range [from,to) from disk.
             * @param from starting line number.
             * @param to ending line number.
             * @exception FileException
             */
            void read(int from, int to) throw (FileException);
            
            /** Write history to disk.
             * @exception FileException
             */
            void write() throw (FileException);

            /** Get raw history list (NULL-terminated C array of HistoryEntry
             * pointers).
             */
            inline HistoryList raw_list() const;

            /** Function template that returns a container of the specified type
             * filled with the contents of the current history list (as returned
             * by the raw_list() member function).  Note that the template
             * argument must be explicitly specified.  The implicit interface
             * assumes that the template type has a constructor that accepts a
             * range.
             */
            template <typename Container>
            inline Container list() const;

            /// Get current size of history list.
            inline size_type size() const;

        private:
            void _init() throw();

            std::string _path;
            mutable HistoryState *_state;
    };

    inline const std::string&
    History::path() const
    {
        return _path;
    }

    inline void
    History::set_path(const std::string& path)
    {
        _path.assign(path);
    }

    inline void
    History::add(const std::string& line)
    {
        add_history(line.c_str());
        state();
    }

    inline HistoryEntry *
    History::remove(int offset)
    {
        HistoryEntry *tmp = remove_history(offset);
        state();
        return tmp;
    }

    inline HistoryData
    History::free(HistoryEntry *entry)
    {
        return free_history_entry(entry);
    }

    inline HistoryEntry *
    History::replace(int offset, const std::string& line, HistoryData data)
    {
        return replace_history_entry(offset, line.c_str(), data);
    }

    inline int
    History::offset() const
    {
        return where_history();
    }

    inline bool
    History::set_offset(int offset)
    {
        const bool tmp = history_set_pos(offset);
        state();
        return tmp;
    }

    inline HistoryEntry *
    History::current_entry() const
    {
        return current_history();
    }

    inline HistoryEntry *
    History::entry_at_offset(int offset) const
    {
        return history_get(offset);
    }

    inline void
    History::clear()
    {
        clear_history();
        state();
    }

    inline bool
    History::is_stifled() const
    {
        return history_is_stifled();
    }

    inline void
    History::stifle(int max)
    {
        stifle_history(max);
        state();
    }

    inline int
    History::unstifle()
    {
        const int tmp = unstifle_history();
        state();
        return tmp;
    }

    inline HistoryState *
    History::state() const
    {
        _state = history_get_history_state();
        return _state;
    }

    inline void
    History::set_state(HistoryState *state)
    {
        history_set_history_state(state);
        _state = state;
    }

    inline HistoryList
    History::raw_list() const
    {
        state();
        return _state->entries;
    }

    template <typename Container>
    inline Container
    History::list() const
    {
        state();
        return (_state->length ?
            Container(_state->entries, _state->entries + _state->length) :
            Container());
    }

    inline History::size_type
    History::size() const
    {
        return history_length;
    }

} // namespace rl

#endif /* HAVE_LIBREADLINE___HISTORY_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
