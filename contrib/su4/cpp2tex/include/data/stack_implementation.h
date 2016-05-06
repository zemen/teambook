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

template <typename Type>
  tamias::Stack<Type>::Stack() : AbstractData(), mSize(0)
  {
  }

template <typename Type>
  tamias::Stack<Type>::Stack( Stack const &stack ) : AbstractData(stack.mSize * sizeof(Type)), mSize(stack.mSize)
  {
    for (sizetype i = 0; i < mSize; i++)
      new ((Type*)data() + i) Type(*((Type*)stack.data() + i));
  }

template <typename Type>
  tamias::Stack<Type>& tamias::Stack<Type>::operator = ( Stack const &stack )
  {
    for (sizetype i = 0; i < mSize; i++)
      ((Type*)data() + i)->~Type();
    mSize = stack.mSize;
    manualReserve(mSize * sizeof(Type));
    for (sizetype i = 0; i < mSize; i++)
      new ((Type*)data() + i) Type(*((Type*)stack.data() + i));
    return *this;
  }

template <typename Type>
  tamias::Stack<Type>::~Stack()
  {
    for (sizetype i = 0; i < mSize; i++)
      ((Type*)data() + i)->~Type();
    mSize = 0;
  }

template <typename Type>
  bool tamias::Stack<Type>::empty() const
  {
    return mSize == 0;
  }

template <typename Type>
  tamias::sizetype tamias::Stack<Type>::size() const
  {
    return mSize;
  }

template <typename Type>
  Type const& tamias::Stack<Type>::top() const
  {
    return (*this)[0];
  }

template <typename Type>
  Type& tamias::Stack<Type>::top()
  {
    return (*this)[0];
  }

template <typename Type>
  Type const& tamias::Stack<Type>::operator[]( sizetype index ) const
  {
    utilities::assert<OutOfBoundsException>(index < mSize);
    return *((Type*)data() + (mSize - 1 - index));
  }

template <typename Type>
  Type& tamias::Stack<Type>::operator[]( sizetype index )
  {
    utilities::assert<OutOfBoundsException>(index < mSize);
    return *((Type*)data() + (mSize - 1 - index));
  }

template <typename Type>
  tamias::Stack<Type>& tamias::Stack<Type>::push( Type const &value )
  {
    autoReserveUp((mSize + 1) * sizeof(Type));
    new ((Type*)data() + mSize++) Type(value);
    return *this;
  }

template <typename Type>
  Type tamias::Stack<Type>::pop()
  {
    Type result = top();
    ((Type*)data() + --mSize)->~Type();
    autoReserve(mSize * sizeof(Type));
    return result;
  }

