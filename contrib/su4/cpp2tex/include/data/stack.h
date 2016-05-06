/*
 * This file [data/stack.h] is part of the “libtamias” library
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
  template <typename Type> class Stack;
}

#include <new>
#include "../basic/abstract_data.h"
#include "../basic/types.h"

template <typename Type>
  class tamias::Stack : private hidden::AbstractData {
    public:
      Stack();
      Stack( Stack const &stack );
      Stack& operator = ( Stack const &stack );
      ~Stack();

      bool empty() const;
      sizetype size() const;
      Type const& top() const;
      Type& top();
      Type const& operator[]( sizetype index ) const;
      Type& operator[]( sizetype index );
      Stack& push( Type const &value );
      Type pop();

    private:
      sizetype mSize;
  };

#include "stack_implementation.h"

