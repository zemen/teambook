/*
 * This file [data/queue_implementation.h] is part of the “libtamias” library
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
  tamias::Queue<Type>::Queue() : hidden::AbstractData(), mStart(0), mSize(0)
  {
  }

template <typename Type>
  tamias::Queue<Type>::Queue( Queue const &queue ) : AbstractData(queue.mSize * sizeof(Type)), mStart(0), mSize(queue.mSize)
  {
    for (sizetype i = 0; i < mSize; i++)
      new ((Type*)data + i) Type(((Type*)queue.data)[i]);
  }

template <typename Type>
  tamias::Queue<Type>& tamias::Queue<Type>::operator = ( Queue const &queue )
  {
    for (sizetype i = 0; i < mSize; i++)
      ((Type*)data)[mStart + i].~Type();
    mStart = 0;
    mSize = queue.mSize;
    manualReserve(mSize * sizeof(Type));
    for (sizetype i = 0; i < mSize; i++)
      new ((Type*)data + i) Type(((Type*)queue.data)[i]);
    return *this;
  }

template <typename Type>
  tamias::Queue<Type>::~Queue()
  {
    for (sizetype i = 0; i < mSize; i++)
      ((Type*)data)[mStart + i].~Type();
    mSize = mStart = 0;
  }

template <typename Type>
  tamias::sizetype tamias::Queue<Type>::size() const
  {
    return mSize;
  }

template <typename Type>
  void tamias::Queue<Type>::push( Type const &item )
  {
    autoReserveUp((mStart + mSize + 1) * sizeof(Type));
    new ((Type*)data + mStart + mSize) Type(item);
    mSize++;
  }

template <typename Type>
  Type tamias::Queue<Type>::pop()
  {
    Type result = ((Type*)data)[mStart];
    ((Type*)data)[mStart].~Type();
    mStart++, mSize--;
    if (mStart > mSize) { // The magic force of amortized analysis starts here.
      for (sizetype i = 0; i < mSize; i++) {
        new ((Type*)data + i) Type(((Type*)data)[mStart + i]);
        ((Type*)data)[mStart + i].~Type();
      }
      mStart = 0;
      manualReserve(mSize * sizeof(Type));
    }
    return result;
  }

template <typename Type>
  Type& tamias::Queue<Type>::front()
  {
    return ((Type*)data)[mStart];
  }

template <typename Type>
  Type const& tamias::Queue<Type>::front() const
  {
    return ((Type*)data)[mStart];
  }

