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

template <typename Type>
  tamias::Array<Type>::Array() : mIt(), mData()
  {
  }

template <typename Type>
  tamias::Array<Type>::Array( Array const &array ) : mIt(array.mIt), mData(array.mData)
  {
  }

template <typename Type>
  tamias::Array<Type>& tamias::Array<Type>::operator = ( Array const &array )
  {
    mIt = array.mIt;
    mData = array.mData;
    return *this;
  }

template <typename Type>
  tamias::Array<Type>::~Array()
  {
  }

template <typename Type>
  tamias::sizetype tamias::Array<Type>::insert( Type const &element )
  {
    sizetype index = it_jumpZero(0, 0);
    if (index < mData.size())
      mData[index] = element, it_change(index, +1);
    else
      index = mData.size(), mData.pushBack(element), it_create(1);
    return index;
  }

template <typename Type>
  Type const& tamias::Array<Type>::operator[]( sizetype index ) const
  {
    utilities::assert<OutOfBoundsException>(index < mData.size() && it_get(index) == 1);
    return mData[index];
  }

template <typename Type>
  Type& tamias::Array<Type>::operator[]( sizetype index )
  {
    utilities::assert<OutOfBoundsException>(index < mData.size() && it_get(index) == 1);
    return mData[index];
  }

template <typename Type>
  void tamias::Array<Type>::erase( sizetype index )
  {
    utilities::assert<OutOfBoundsException>(index < mData.size() && it_get(index) == 1);
    mData[index] = Type(); // OLOLO
    it_change(index, -1);
    // TODO: delete something if last (index == mData.size() - 1)
  }

template <typename Type>
  tamias::sizetype tamias::Array<Type>::first() const
  {
    return it_jumpOne(0, 0);
  }

template <typename Type>
  tamias::sizetype tamias::Array<Type>::next( sizetype index ) const
  {
    utilities::assert<OutOfBoundsException>(index < mData.size() && it_get(index) == 1);
    return it_jumpOne(index, 1);
  }

// magic begins here

template <typename Type>
  void tamias::Array<Type>::it_change( sizetype index, sizetype add )
  {
    index *= 2;
    mIt[index] += add;
    sizetype level = 0, n = mIt.size();
    while (true) {
      bool left = ((index - (1 << level) + 1) >> (level + 1)) % 2 == 0;
      sizetype parent = left ? index + (1 << level) : index - (1 << level);
      if (parent < n)
        mIt[parent] += add;
      else if ((parent & (1 + parent)) == 0)
        break;
      index = parent;
      level++;
    }
  }

template <typename Type>
  void tamias::Array<Type>::it_create( sizetype value )
  {
    if (mIt.size() != 0) {
      sizetype vertex = mIt.size(), level = 0;
      while ((vertex & ((2u << level) - 1)) == (2u << level) - 1)
        level++; level--; // obfuscated code, huh
      mIt.pushBack(mIt[vertex - (1 << level)]);
    }
    mIt.pushBack(0);
    it_change((mIt.size() - 1) / 2, value);
  }

template <typename Type>
  tamias::sizetype tamias::Array<Type>::it_get( sizetype index ) const
  {
    return mIt[index * 2];
  }

template <typename Type>
  tamias::sizetype tamias::Array<Type>::it_jumpOne( sizetype index, sizetype length ) const
  {
    sizetype n = mIt.size(), level = 0;
    index *= 2;
    while (true)
      if (index >= n || length < mIt[index]) {
        if (level == 0)
          return index < n ? index / 2 : (sizetype)-1;
        level--;
        sizetype left = index - (1 << level), right = index + (1 << level);
        if (left >= n || length < mIt[left])
          index = left;
        else
          index = right, length -= mIt[left];
      } else {
        bool left = ((index - (1 << level) + 1) >> (level + 1)) % 2 == 0;
        sizetype parent = left ? index + (1 << level) : index - (1 << level);
        level++;
        if (!left)
          length += mIt[index - (1 << level)];
        index = parent;
      }
  }

template <typename Type>
  tamias::sizetype tamias::Array<Type>::it_jumpZero( sizetype index, sizetype length ) const
  {
    sizetype n = mIt.size(), level = 0;
    index *= 2;
    while (true)
      if (index >= n || length < (1 << level) - mIt[index]) {
        if (level == 0)
          return index < n ? index / 2 : (sizetype)-1;
        level--;
        sizetype left = index - (1 << level), right = index + (1 << level);
        if (left >= n || length < (1 << level) - mIt[left])
          index = left;
        else
          index = right, length -= (1 << level) - mIt[left];
      } else {
        bool left = ((index - (1 << level) + 1) >> (level + 1)) % 2 == 0;
        sizetype parent = left ? index + (1 << level) : index - (1 << level);
        if (!left)
          length += (1 << level) - mIt[index - (2 << level)];
        level++;
        index = parent;
      }
  }

/*
 * ......3......
 * /.../-/.\-\...
 * ..1.......5..
 * ./.\...../.\.
 * 0...2...4...6
 */

