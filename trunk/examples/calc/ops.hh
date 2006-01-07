/*
 * libreadlinepp -- examples/calc/calcop.hh
 * $Id$
 * Copyright (c) 2006 Aaron Walker <ka0ttic@gentoo.org>
 *
 * This file is part of libreadlinepp.
 *
 * libreadlinepp is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * libreadlinepp is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * libreadlinepp; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 325, Boston, MA  02111-1257  USA
 */

#ifndef _HAVE_CALC_CALCOP_HH
#define _HAVE_CALC_CALCOP_HH 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

class CalcOp
{
    public:
        virtual ~CalcOp() { }
        virtual float operator()(float p1, float p2) const = 0;
};

class AddOp : public CalcOp
{
    public:
        virtual ~AddOp() { }
        virtual float operator()(float p1, float p2) const
        { return (p1 + p2); }
};

class SubtractOp : public CalcOp
{
    public:
        virtual ~SubtractOp() { }
        virtual float operator()(float p1, float p2) const
        { return (p1 - p2); }
};

class MultiplyOp : public CalcOp
{
    public:
        virtual ~MultiplyOp() { }
        virtual float operator()(float p1, float p2) const
        { return (p1 * p2); }
};

class DivideOp : public CalcOp
{
    public:
        virtual ~DivideOp() { }
        virtual float operator()(float p1, float p2) const
        { return (p1 / p2); }
};

#endif /* _HAVE_CALC_CALCOP_HH */

/* vim: set tw=80 sw=4 fdm=marker et : */
