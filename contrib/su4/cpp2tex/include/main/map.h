/*
 * This file [main/map.h] is part of the “libtamias” library
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

#pragma once

#include "../basic/types.h"
#include "../data/pair.h"

namespace tamias
{
  namespace hidden
  {
    template <typename KeyType, typename ValueType>
      class MapElement : public Pair <KeyType, ValueType>
      {
        public:
          MapElement();
          MapElement( const KeyType &key, const ValueType &value );
          MapElement( const MapElement <KeyType, ValueType> &element );
          ~MapElement();
          MapElement& operator = ( const MapElement <KeyType, ValueType> &element );

          bool operator < ( const MapElement<KeyType, ValueType> &element ) const;
      };
  }

  template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
    class Map
    {
      public:
        typedef typename CollectionTemplate <hidden::MapElement <Key, Value> > ::Iterator Iterator;
        typedef typename CollectionTemplate <hidden::MapElement <Key, Value> > ::ConstIterator ConstIterator;
      private:
        CollectionTemplate <hidden::MapElement <Key, Value> > collection;
        Value empty;
      public:
        Map();
        Map( const Map <CollectionTemplate, Key, Value> &map );
        ~Map();
        Map& operator = ( const Map <CollectionTemplate, Key, Value> &map );

        const Value& operator [] ( const Key &key ) const;
        Value& operator [] ( const Key &key );
        sizetype count( const Key &key ) const;
        void erase( const Key &key );
        Iterator begin();
        Iterator end();
        ConstIterator begin() const;
        ConstIterator end() const;

        void clear();
    };
}

template <typename KeyType, typename ValueType>
  tamias::hidden::MapElement <KeyType, ValueType> ::MapElement() : Pair <KeyType, ValueType> ()
  {
  }

template <typename KeyType, typename ValueType>
  tamias::hidden::MapElement <KeyType, ValueType> ::MapElement( const KeyType &key, const ValueType &value )
                : Pair <KeyType, ValueType> (key, value)
  {
  }

template <typename KeyType, typename ValueType>
  tamias::hidden::MapElement <KeyType, ValueType> ::MapElement( const MapElement <KeyType, ValueType> &element )
                : Pair <KeyType, ValueType> (element.first, element.second)
  {
  }

template <typename KeyType, typename ValueType>
  tamias::hidden::MapElement <KeyType, ValueType> ::~MapElement()
  {
  }

template <typename KeyType, typename ValueType>
  tamias::hidden::MapElement <KeyType, ValueType>&
  tamias::hidden::MapElement <KeyType, ValueType> ::operator = ( const MapElement <KeyType, ValueType> &element )
  {
    this->first = element.first;
    this->second = element.second;
    return *this;
  }

template <typename KeyType, typename ValueType>
  bool tamias::hidden::MapElement<KeyType, ValueType>::operator < ( const MapElement<KeyType, ValueType> &element ) const
  {
    return this->first < element.first;
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  tamias::Map <CollectionTemplate, Key, Value> ::Map() : collection()
  {
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  tamias::Map <CollectionTemplate, Key, Value> ::Map( const Map <CollectionTemplate, Key, Value> &map )
                                               : collection(map.collection)
  {
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  tamias::Map <CollectionTemplate, Key, Value> ::~Map()
  {
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  tamias::Map <CollectionTemplate, Key, Value>&
  tamias::Map <CollectionTemplate, Key, Value> ::operator = ( const Map <CollectionTemplate, Key, Value> &map )
  {
    collection = map.collection;
    return *this;
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  const Value& tamias::Map <CollectionTemplate, Key, Value>::operator [] ( const Key &key ) const
  {
    tamias::hidden::MapElement<Key, Value> element(key, Value());
    if (collection.count(element) == 0)
      return empty;
    const tamias::hidden::MapElement<Key, Value> &result = *(collection.find(element));
    return result.second;
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  Value& tamias::Map <CollectionTemplate, Key, Value>::operator [] ( const Key &key )
  {
    tamias::hidden::MapElement<Key, Value> element(key, Value());
    if (collection.count(element) == 0)
      collection.add(element);
    tamias::hidden::MapElement<Key, Value> &result = *(collection.find(element));
    return result.second;
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  tamias::sizetype tamias::Map <CollectionTemplate, Key, Value> ::count( const Key &key ) const
  {
    return collection.count(tamias::hidden::MapElement <Key, Value> (key, Value()));
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  void tamias::Map <CollectionTemplate, Key, Value> ::erase( const Key &key )
  {
    collection.erase(tamias::hidden::MapElement <Key, Value> (key, Value()));
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  typename tamias::Map <CollectionTemplate, Key, Value> ::Iterator tamias::Map <CollectionTemplate, Key, Value> ::begin()
  {
    return collection.begin();
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  typename tamias::Map <CollectionTemplate, Key, Value> ::Iterator tamias::Map <CollectionTemplate, Key, Value> ::end()
  {
    return collection.end();
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  typename tamias::Map <CollectionTemplate, Key, Value> ::ConstIterator
           tamias::Map <CollectionTemplate, Key, Value> ::begin() const
  {
    return collection.begin();
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  typename tamias::Map <CollectionTemplate, Key, Value> ::ConstIterator
            tamias::Map <CollectionTemplate, Key, Value> ::end() const
  {
    return collection.end();
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  void tamias::Map <CollectionTemplate, Key, Value> ::clear()
  {
    collection.clear();
  }

