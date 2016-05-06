/*
 * This file [tests/test_000.cpp] is part of the “libtamias” library
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

/*
 * Testing types sizes.
 */

#include "../../include/basic/types.h"

int main()
{
  if (sizeof(tamias::inttype8) != 1) return 1;
  if (sizeof(tamias::uinttype8) != 1) return 1;
  if (sizeof(tamias::inttype16) != 2) return 1;
  if (sizeof(tamias::uinttype16) != 2) return 1;
  if (sizeof(tamias::inttype32) != 4) return 1;
  if (sizeof(tamias::uinttype32) != 4) return 1;
  if (sizeof(tamias::inttype64) != 8) return 1;
  if (sizeof(tamias::uinttype64) != 8) return 1;
  if (sizeof(tamias::chartype) != 4) return 1;
  if (sizeof(tamias::sizetype) < 4) return 1;
  return 0;
}

