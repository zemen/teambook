/*
 * This file [data/map_implementation.h] is part of the “libtamias” library
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


// template MapElement

template <typename KeyType, typename ValueType>
  tamias::hidden::MapElement<KeyType, ValueType>::MapElement() : Pair<KeyType, ValueType>()
  {
  }

template <typename KeyType, typename ValueType>
  tamias::hidden::MapElement<KeyType, ValueType>::MapElement( KeyType const &key, ValueType const &value ) : Pair<KeyType, ValueType>(key, value)
  {
  }

template <typename KeyType, typename ValueType>
  tamias::hidden::MapElement<KeyType, ValueType>::MapElement( MapElement <KeyType, ValueType> const &element ) : Pair<KeyType, ValueType>(element.first, element.second)
  {
  }

template <typename KeyType, typename ValueType>
  tamias::hidden::MapElement<KeyType, ValueType>& tamias::hidden::MapElement<KeyType, ValueType>::operator = ( MapElement <KeyType, ValueType> const &element )
  {
    this->first = element.first;
    this->second = element.second;
    return *this;
  }

template <typename KeyType, typename ValueType>
  tamias::hidden::MapElement<KeyType, ValueType>::~MapElement()
  {
  }

template <typename KeyType, typename ValueType>
  bool tamias::hidden::MapElement<KeyType, ValueType>::operator < ( MapElement<KeyType, ValueType> const &element ) const
  {
    return this->first < element.first;
  }


// template Map

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  tamias::Map<CollectionTemplate, Key, Value>::Map() : collection(), empty()
  {
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  tamias::Map<CollectionTemplate, Key, Value>::Map( Map <CollectionTemplate, Key, Value> const &map ) : collection(map.collection), empty()
  {
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  tamias::Map<CollectionTemplate, Key, Value>& tamias::Map<CollectionTemplate, Key, Value>::operator = ( Map <CollectionTemplate, Key, Value> const &map )
  {
    collection = map.collection;
    return *this;
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  tamias::Map<CollectionTemplate, Key, Value>::~Map()
  {
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  tamias::sizetype tamias::Map<CollectionTemplate, Key, Value>::size() const
  {
    return collection.size();
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  Value& tamias::Map<CollectionTemplate, Key, Value>::operator [] ( Key const &key )
  {
    tamias::hidden::MapElement<Key, Value> element(key, Value());
    if (collection.count(element) == 0)
      collection.insert(element);
    tamias::hidden::MapElement<Key, Value> &result = *(collection.find(element));
    return result.second;
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  Value const& tamias::Map<CollectionTemplate, Key, Value>::operator [] ( Key const &key ) const
  {
    tamias::hidden::MapElement<Key, Value> element(key, Value());
    if (collection.count(element) == 0)
      return empty;
    tamias::hidden::MapElement<Key, Value> const &result = *(collection.find(element));
    return result.second;
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  tamias::sizetype tamias::Map<CollectionTemplate, Key, Value>::count( Key const &key ) const
  {
    return collection.count(tamias::hidden::MapElement <Key, Value> (key, Value()));
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  void tamias::Map<CollectionTemplate, Key, Value>::erase( Key const &key )
  {
    collection.erase(tamias::hidden::MapElement<Key, Value>(key, Value()));
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  typename tamias::Map<CollectionTemplate, Key, Value>::Iterator tamias::Map<CollectionTemplate, Key, Value>::begin()
  {
    return collection.begin();
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  typename tamias::Map<CollectionTemplate, Key, Value>::Iterator tamias::Map<CollectionTemplate, Key, Value>::end()
  {
    return collection.end();
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  typename tamias::Map<CollectionTemplate, Key, Value>::ConstIterator tamias::Map<CollectionTemplate, Key, Value>::begin() const
  {
    return collection.begin();
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  typename tamias::Map<CollectionTemplate, Key, Value>::ConstIterator tamias::Map<CollectionTemplate, Key, Value>::end() const
  {
    return collection.end();
  }

template <template <typename Type> class CollectionTemplate, typename Key, typename Value>
  void tamias::Map<CollectionTemplate, Key, Value>::clear()
  {
    collection.clear();
  }

