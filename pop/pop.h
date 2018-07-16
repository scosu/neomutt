/**
 * @file
 * POP network mailbox
 *
 * @authors
 * Copyright (C) 2000-2003 Vsevolod Volkov <vvv@mutt.org.ua>
 *
 * @copyright
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _POP_POP_H
#define _POP_POP_H

#include "mx.h"

/* These Config Variables are only used in pop/pop.c */
extern short         PopCheckinterval;
extern unsigned char PopDelete;
extern char *        PopHost;
extern bool          PopLast;

/* These Config Variables are only used in pop/pop_auth.c */
extern char *PopAuthenticators;
extern bool  PopAuthTryAll;

/* These Config Variables are only used in pop/pop_lib.c */
extern unsigned char PopReconnect;

extern struct MxOps mx_pop_ops;

void pop_fetch_mail(void);

#endif /* _POP_POP_H */