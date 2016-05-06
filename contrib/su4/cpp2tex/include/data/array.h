/*
 * This file [data/array.h] is part of the “libtamias” library
 * Copyright (c) 2007-2010 Oleg Davydov, Yury Petrov
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

#pragma once

namespace tamias {
  template <typename Type> class Array; // special data structure
}

#include "../basic/generic_exception.h"
#include "../basic/types.h"
#include "../basic/utilities.h"
#include "../data/pair.h"
#include "../data/vector.h"

template <typename Type>
  class tamias::Array {
    public:
      Array();
      Array( Array const &array );
      Array& operator = ( Array const &array );
      ~Array();

      sizetype insert( Type const &element ); // inserts element into first free position, returns this position
      Type const& operator[]( sizetype index ) const;
      Type& operator[]( sizetype index );
      void erase( sizetype index );
      sizetype first() const;
      sizetype next( sizetype index ) const; // -1 for no element

    private:
      Vector <sizetype> mIt;
      Vector <Type> mData;

      // Theese functions rely on correct parameters!
      void it_change( sizetype index, sizetype add );
      void it_create( sizetype value );
      sizetype it_get( sizetype index ) const;
      sizetype it_jumpOne( sizetype start, sizetype length ) const;
      sizetype it_jumpZero( sizetype start, sizetype length ) const;
      // “it” means interval tree
  };

// TODO
//  — upgrade this class to work with types without default value

#include "array_implementation.h"

