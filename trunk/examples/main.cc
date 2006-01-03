/*
 * libreadline++ -- examples/main.cc
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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <iostream>
#include <list>
#include <cstdlib>
#include <libreadline++/libreadline++.hh>

struct PrintLineFromHistEntry
{
    void operator()(rl::HistoryEntry *entry) const
    {
        if (not entry or not entry->line)
            return;
        else if (not *(entry->line))
            std::cout << "!!! (empty entry)" << std::endl;
        else
            std::cout << "!!! entry = '" << entry->line << "'." << std::endl;
    }
};

int main()
{
    try
    {
        rl::ReadLine rl("myapp", "prompt> ");
        rl::History history("myapp-history");

        // read previously saved history in $PWD/myapp-history
        history.read();

        std::cout << "!!! history size = " << history.size() << std::endl;

        std::list<rl::HistoryEntry *> list =
            history.list<std::list<rl::HistoryEntry *> >();
        std::for_each(list.begin(), list.end(), PrintLineFromHistEntry());

        try
        {
            while (true)
            {
                // read line from user
                std::string in(rl());

                if (in.empty())
                    continue;
                if (in == "quit" or in == "exit")
                    throw rl::ReadLineEOF();

                // add it to the history
                history.add(in);

                /* of course a real application would do something useful
                 * with the input... */
                std::cout << "Read input '" << in << "'." << std::endl;
            }
        }
        catch (const rl::ReadLineEOF&)
        {
            std::cerr << "exiting..." << std::endl;
        }

        // write history to $PWD/myapp-history
        history.write();
        std::cout << "!!! history size = " << history.size() << std::endl;
    }
    catch (const rl::FileException& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (const rl::BaseException& e)
    {
        std::cerr << "Uncaught exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/* vim: set tw=80 sw=4 fdm=marker et : */
