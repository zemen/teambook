/*
 * This file [data/map.h] is part of the “libtamias” library
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
  namespace hidden {
    template <typename KeyType, typename ValueType> class MapElement;
  }
  template <template <typename Type> class CollectionTemplate, typename Key, typename Value> class Map;
}

#include "../basic/types.h"
#include "../data/pair.h"

template <typename KeyType, typename ValueType>
  class tamias::hidden::MapElement : public Pair <KeyType, ValueType> {
    public:
      MapElement();
      MapElement( KeyType const &key, ValueType const &value );
      MapElement( MapElement <KeyType, ValueType> const &element );
      MapElement& operator = ( MapElement <KeyType, ValueType> const &element );
      ~MapElement();

      bool operator < ( const MapElement<KeyType, ValueType> &element ) const;
  };

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  class tamias::Map {
    public:
      typedef typename CollectionTemplate<hidden::MapElement <Key, Value> >::Iterator Iterator;
      typedef typename CollectionTemplate<hidden::MapElement <Key, Value> >::ConstIterator ConstIterator;
      // TODO: reverse iterators

    public:
      Map();
      Map( Map <CollectionTemplate, Key, Value> const &map );
      Map& operator = ( Map <CollectionTemplate, Key, Value> const &map );
      ~Map();

      sizetype size() const;
      Value& operator [] ( Key const &key );
      Value const& operator [] ( Key const &key ) const;

      sizetype count( Key const &key ) const;
      void erase( Key const &key );

      Iterator begin();
      Iterator end();
      ConstIterator begin() const;
      ConstIterator end() const;

      void clear();

    private:
      CollectionTemplate <hidden::MapElement <Key, Value> > collection;
      Value empty;
  };

#include "map_implementation.h"

