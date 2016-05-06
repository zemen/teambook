/*
 * This file [data/vector.h] is part of the “libtamias” library
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
  template <typename Type> class Vector;
  template <typename Type> class VectorCreator;
}

#include <new> // for constructor invoking
#include "../basic/abstract_data.h"
#include "../basic/generic_exception.h"
#include "../basic/iterator.h"

template <typename Type>
  class tamias::Vector : private hidden::AbstractData {
    public:
      typedef Type* Pointer;
      typedef Type& Reference;
      typedef Type const* ConstPointer;
      typedef Type const& ConstReference;
      typedef hidden::DefaultIterator <Pointer> Iterator;
      typedef hidden::DefaultConstIterator <Pointer> ConstIterator;
      typedef hidden::DefaultReverseIterator <Pointer> ReverseIterator;
      typedef hidden::DefaultConstReverseIterator <Pointer> ConstReverseIterator;

    public:
      Vector();
      Vector( sizetype initialSize, Type const &value = Type() );
      Vector( Vector <Type> const &vector );
      Vector& operator = ( Vector const &vector );
      ~Vector();

      sizetype size() const;
      Reference operator [] ( sizetype index );
      ConstReference operator [] ( sizetype index ) const;

      Iterator begin();
      Iterator end();
      ConstIterator begin() const;
      ConstIterator end() const;
      ReverseIterator rbegin();
      ReverseIterator rend();
      ConstReverseIterator rbegin() const;
      ConstReverseIterator rend() const;

      void clear();
      void resize( sizetype newSize );
      void pushBack( Type const &item );

    private:
      sizetype mSize;
  };

template <typename Type>
  class tamias::VectorCreator {
    public:
      VectorCreator();
      VectorCreator( Type const &value );
      VectorCreator( VectorCreator const &creator );
      VectorCreator& operator = ( VectorCreator const &creator );
      ~VectorCreator();

      VectorCreator& operator () ( Type const &value );
      VectorCreator& operator << ( Type const &value );
      operator Vector <Type> () const;

    private:
      Vector <Type> result;
  };

#include "vector_implementation.h"

