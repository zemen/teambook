/*
 * This file [basic/types.h] is part of the “libtamias” library
 * Copyright (c) 2007-2009 Oleg Davydov, Yury Petrov
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Our contacts:
 *   mailto: burunduk3@gmail.com (Oleg Davydov)
 *   mailto: jpsbur@gmail.com (Yury Petrov)
 */

#ifndef _libtamias_basic_types_
#define _libtamias_basic_types_

namespace tamias
{
/* These types are correct on i386+ and x86_64 archetictures */
/* But I think that on x86_64 int should be 64-bit, not long */
  typedef char inttype8;
  typedef unsigned char uinttype8;
  typedef short int inttype16;
  typedef unsigned short int uinttype16;
  typedef int inttype32;
  typedef unsigned int uinttype32;
  typedef long long inttype64;
  typedef unsigned long long uinttype64;

  typedef unsigned long sizetype; /* 32-bit on i386+ and 64-bit on x86_64 */
  typedef uinttype32 chartype;    /* utf32 character */
}

#endif /* _libtamias_basic_types_ */

