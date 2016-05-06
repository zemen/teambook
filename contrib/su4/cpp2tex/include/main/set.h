/*
 * This file [main/set.h] is part of the “libtamias” library
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

#ifndef _libtamias_main_set_h_
#define _libtamias_main_set_h_

#include "../basic/types.h"

namespace tamias
{
  template <template <typename Type> class CollectionTemplate, typename Type>
    class Set
    {
      public:
        typedef typename CollectionTemplate <Type> ::Iterator Iterator;
      private:
        CollectionTemplate <Type> collection;
      public:
        Set();
        Set( const Set <CollectionTemplate, Type> &set );
        ~Set();
        Set& operator = ( const Set &set );

        sizetype size() const;
        void insert( const Type &value );
        void erase( const Type &value );
        sizetype count( const Type &value ) const;
        Iterator begin();
        Iterator end();
        // TODO: other iterators, methods etc
    };
}

template <template <typename Type> class CollectionTemplate, typename Type>
  tamias::Set <CollectionTemplate, Type> ::Set() : collection()
  {
  }

template <template <typename Type> class CollectionTemplate, typename Type>
  tamias::Set <CollectionTemplate, Type> ::Set( const Set &set ) : collection(set.collection)
  {
  }

template <template <typename Type> class CollectionTemplate, typename Type>
  tamias::Set <CollectionTemplate, Type> ::~Set()
  {
  }

template <template <typename Type> class CollectionTemplate, typename Type>
  tamias::Set <CollectionTemplate, Type>& tamias::Set <CollectionTemplate, Type> ::operator = ( const Set &set )
  {
    collection = set.collection;
    return *this;
  }

template <template <typename Type> class CollectionTemplate, typename Type>
  tamias::sizetype tamias::Set <CollectionTemplate, Type> ::size() const
  {
    return collection.size();
  }

template <template <typename Type> class CollectionTemplate, typename Type>
  void tamias::Set <CollectionTemplate, Type> ::insert( const Type &value )
  {
    collection.add(value);
  }

template <template <typename Type> class CollectionTemplate, typename Type>
  void tamias::Set <CollectionTemplate, Type> ::erase( const Type &value )
  {
    collection.erase(value);
  }

template <template <typename Type> class CollectionTemplate, typename Type>
  tamias::sizetype tamias::Set <CollectionTemplate, Type> ::count( const Type &value ) const
  {
    return collection.count(value);
  }

template <template <typename Type> class CollectionTemplate, typename Type>
  typename tamias::Set <CollectionTemplate, Type> ::Iterator tamias::Set <CollectionTemplate, Type> ::begin()
  {
    return collection.begin();
  }

template <template <typename Type> class CollectionTemplate, typename Type>
  typename tamias::Set <CollectionTemplate, Type> ::Iterator tamias::Set <CollectionTemplate, Type> ::end()
  {
    return collection.end();
  }

#endif /* _libtamias_main_set_h_ */

