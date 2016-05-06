/*
 * This file [data/set_implementation.h] is part of the “libtamias” library
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

template <template <typename Type> class CollectionTemplate, typename Type>
  tamias::Set<CollectionTemplate, Type>::Set() : collection()
  {
  }

template <template <typename Type> class CollectionTemplate, typename Type>
  tamias::Set<CollectionTemplate, Type>::Set( Set const &set ) : collection(set.collection)
  {
  }

template <template <typename Type> class CollectionTemplate, typename Type>
  tamias::Set<CollectionTemplate, Type>& tamias::Set <CollectionTemplate, Type>::operator = ( Set const &set )
  {
    collection = set.collection;
    return *this;
  }

template <template <typename Type> class CollectionTemplate, typename Type>
  tamias::Set<CollectionTemplate, Type>::~Set()
  {
  }

template <template <typename Type> class CollectionTemplate, typename Type>
  tamias::sizetype tamias::Set<CollectionTemplate, Type>::size() const
  {
    return collection.size();
  }

template <template <typename Type> class CollectionTemplate, typename Type>
  void tamias::Set<CollectionTemplate, Type>::insert( Type const &value )
  {
    collection.insert(value);
  }

template <template <typename Type> class CollectionTemplate, typename Type>
  void tamias::Set<CollectionTemplate, Type>::erase( Type const &value )
  {
    collection.erase(value);
  }

template <template <typename Type> class CollectionTemplate, typename Type>
  tamias::sizetype tamias::Set<CollectionTemplate, Type>::count( Type const &value ) const
  {
    return collection.count(value);
  }

template <template <typename Type> class CollectionTemplate, typename Type>
  typename tamias::Set<CollectionTemplate, Type>::Iterator tamias::Set<CollectionTemplate, Type>::begin()
  {
    return collection.begin();
  }

template <template <typename Type> class CollectionTemplate, typename Type>
  typename tamias::Set<CollectionTemplate, Type>::Iterator tamias::Set<CollectionTemplate, Type>::end()
  {
    return collection.end();
  }

template <template <typename Type> class CollectionTemplate, typename Type>
  typename tamias::Set<CollectionTemplate, Type>::ConstIterator tamias::Set<CollectionTemplate, Type>::begin() const
  {
    return collection.begin();
  }

template <template <typename Type> class CollectionTemplate, typename Type>
  typename tamias::Set<CollectionTemplate, Type>::ConstIterator tamias::Set<CollectionTemplate, Type>::end() const
  {
    return collection.end();
  }

