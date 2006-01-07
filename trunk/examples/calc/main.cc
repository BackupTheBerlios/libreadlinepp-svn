/*
 * libreadline++ -- examples/calc/main.cc
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
#include <map>
#include <vector>
#include <string>
#include <cstdlib>
#include <libreadline++/util.hh>
#include <libreadline++/libreadline++.hh>
#include "ops.hh"

static std::vector<std::string>
split(const std::string& str, const char delim)
{
    std::vector<std::string> v;
    std::string::size_type pos, lpos = 0;
 
    while (true)
    {
        if ((pos = str.find(delim, lpos)) == std::string::npos)
        {
            v.push_back(str.substr(lpos));
            break;
        }
        
        /* don't append empty strings (two         
         * delimiters in a row were encountered) */
        const std::string sub(str.substr(lpos, pos - lpos));
        if (not sub.empty())
            v.push_back(sub);
    
        lpos = ++pos;
    }
    return v;
}

static char *
op_completion(const char *text, int state)
{
    static const char * const ops[] =
        { "add", "subtract", "multiply", "divide" };
    static std::size_t i, len;

    if (state == 0)
    {
        i = 0;
        len = std::strlen(text);
    }

    for (; i < (sizeof(ops) / sizeof(ops[0])) ; ++i)
    {
        if (std::strncmp(ops[i], text, len) == 0)
            return strdup(ops[i++]);
    }

    return NULL;
}

static char **
calc_completion(const char *text, int start, int end)
{
    char **matches = NULL;

    /* Don't have readline use default completion methods (file/directory
     * completion) if this function returns NULL */
    rl_attempted_completion_over = 1;

    /* on first word, so complete on operation names */
    if (start == 0)
        matches = rl_completion_matches(text, op_completion);

    return matches;
}

int main()
{
    try
    {
        std::map<std::string, CalcOp *> opmap;
        opmap["add"] = new AddOp();
        opmap["subtract"] = new SubtractOp();
        opmap["multiply"] = new MultiplyOp();
        opmap["divide"] = new DivideOp();

        rl::ReadLine rl("calc", "calc> ");
        rl::History history("calc-history");

        /* use calc_completion() to generate completions */
        rl.set_attempted_comp_hook(calc_completion);

        /* read previously saved history in $PWD/calc-history */
        history.read();

        try
        {
            while (true)
            {
                /* read line from user */
                std::string &in(rl());

                if (in.empty())
                    continue;
                if (in == "quit" or in == "exit")
                    throw rl::ReadLineEOF();

                std::vector<std::string> parts(split(in, ' '));
                if (parts.size() != 3)
                {
                    std::cerr << "usage: <op> <param1> <param2>" << std::endl;
                    continue;
                }

                std::map<std::string, CalcOp *>::iterator i = opmap.find(parts[0]);
                if (i == opmap.end())
                {
                    std::cerr << "unknown operation '" << parts[0] << "'." << std::endl;
                    continue;
                }

                /* add it to the history */
                history.add(in);

                /* perform operation */
                float result = (*i->second)(rl::destringify<float>(parts[1]),
                                            rl::destringify<float>(parts[2]));

                /* display result */
                std::cout << rl::stringify<float>(result) << std::endl;
            }
        }
        catch (const rl::ReadLineEOF&)
        {
            std::cerr << "exiting..." << std::endl;
        }

        /* write history to $PWD/calc-history */
        history.write();

        std::map<std::string, CalcOp *>::iterator i;
        for (i = opmap.begin() ; i != opmap.end() ; ++i)
        {
            if (i->second)
                delete i->second;
        }
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
