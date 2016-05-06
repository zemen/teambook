/*
 * This file [main/algotrithm.h] is part of the “libtamias” library
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

#ifndef _libtamias_main_algorithm_h_
#define _libtamias_main_algorithm_h_

#include "../basic/iterator.h"
#include "../basic/types.h"

namespace tamias
{
  namespace algorithm
  {
      /* We are using some modification of qsort algorithm. http://en.wikipedia.org/wiki/Quicksort */
    template <typename IteratorType>
      void sort( IteratorType begin, IteratorType end, int depth = 0 );
  }
}

template <typename IteratorType>
  void tamias::algorithm::sort( IteratorType begin, IteratorType end, int depth )
  {
    tamias::sizetype size = 0;
    for (IteratorType it = begin; it != end; it++)
      size++;
    if (size <= 1)
      return;
    tamias::sizetype middle = size / 2; // TODO: random!
    IteratorType it = begin;
    for (sizetype i = 0; i < middle; i++)
      it++;
    typename tamias::hidden::IteratorTypes<IteratorType>::ValueType value = *it;
    IteratorType i = begin, j = begin, k = begin;
    while (i != end)
    {
      if (*i < value)
      {
        typename tamias::hidden::IteratorTypes<IteratorType>::ValueType temp = *i;
        *i = *k, *k = *j;
        *j = temp;
        j++, k++;
      }
      else if (!(value < *i))
      {
        typename tamias::hidden::IteratorTypes<IteratorType>::ValueType temp = *i;
        *i = *k;
        *k = temp;
        k++;
      }
      i++;
    }
    sort(begin, j, depth + 1);
    sort(k, end, depth + 1);
  }

#endif // _libtamias_main_algorithm_h_ 
