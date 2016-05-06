/*
 * This file [basic/utilities.h] is part of the “libtamias” library
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

#ifndef _libtamias_basic_utilities_h_
#define _libtamias_basic_utilities_h_

#include "../basic/types.h"

namespace tamias
{
  namespace utilities
  {
    void memoryCopy( void *target, const void *source, sizetype size );
    void memorySet( void *target, char filler, sizetype size );

    template <typename ValueType>
      ValueType abs( ValueType value );
    template <typename ValueType>
      ValueType min( ValueType value1, ValueType value2 );
    template <typename ValueType>
      ValueType max( ValueType value1, ValueType value2 );
    template <typename ValueType>
      void swap( ValueType &a, ValueType &b );
    template <typename IteratorType>
      void reverse( IteratorType begin, IteratorType end );
    template <typename ExceptionType>
      void assert( bool expression );
    template <typename ExceptionType, typename ErrorType>
      void assert( bool expression, ErrorType error );
  };
}

template <typename ValueType>
  ValueType tamias::utilities::abs( ValueType value )
  {
    if (value < 0)
      return -value;
    return value;
  }

template <typename ValueType>
  ValueType tamias::utilities::min( ValueType value1, ValueType value2 )
  {
    if (value1 <= value2)
      return value1;
    return value2;
  }

template <typename ValueType>
  ValueType tamias::utilities::max( ValueType value1, ValueType value2 )
  {
    if (value1 >= value2)
      return value1;
    return value2;
  }

template <typename ValueType>
  void tamias::utilities::swap( ValueType &a, ValueType &b )
  {
    ValueType c = a;
    a = b, b = c;
  }

template <typename IteratorType>
  void tamias::utilities::reverse( IteratorType begin, IteratorType end )
  {
    while (begin != end)
    {
      end--;
      if (begin == end)
        break;
      swap(*begin, *end);
      begin++;
    }
  }

template <typename ExceptionType>
  void tamias::utilities::assert( bool expression )
  {
    if (!expression)
      throw ExceptionType();
  }

template <typename ExceptionType, typename ErrorType>
  void tamias::utilities::assert( bool expression, ErrorType error )
  {
    if (!expression)
      throw ExceptionType(error);
  }

#endif /* _libtamias_basic_utilities_h_ */

