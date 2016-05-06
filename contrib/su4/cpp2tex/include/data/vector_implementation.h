/*
 * This file [data/vector_implementation.h] is part of the “libtamias” library
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
  tamias::Vector<Type>::Vector() : tamias::hidden::AbstractData(0), mSize(0)
  {
  }

template <typename Type>
  tamias::Vector<Type>::Vector( sizetype initialSize, Type const &value ) : hidden::AbstractData(initialSize * sizeof(Type)), mSize(initialSize)
  {
    for (sizetype i = 0; i < initialSize; i++)
      new ((Type*)data() + i) Type(value);
  }

template <typename Type>
  tamias::Vector<Type>::Vector( Vector <Type> const &vector ) : hidden::AbstractData(vector.mSize * sizeof(Type)), mSize(vector.mSize)
  {
    for (sizetype i = 0; i < mSize; i++)
      new ((Type*)data() + i) Type(vector[i]);
  }

template <typename Type>
  tamias::Vector<Type>& tamias::Vector<Type>::operator = ( Vector const &vector )
  {
    for (sizetype i = 0; i < mSize; i++)
      (*this)[i].~Type();
    mSize = vector.mSize;
    manualReserve(mSize * sizeof(Type));
    for (sizetype i = 0; i < mSize; i++)
      new ((Type*)data() + i) Type(vector[i]);
    return *this;
  }

template <typename Type>
  tamias::Vector<Type>::~Vector()
  {
    for (sizetype i = 0; i < mSize; i++)
      (*this)[i].~Type();
  }

template <typename Type>
  tamias::sizetype tamias::Vector<Type>::size() const
  {
    return mSize;
  }

template <typename Type>
  typename tamias::Vector<Type>::Reference tamias::Vector<Type>::operator [] ( sizetype index )
  {
    utilities::assert<OutOfBoundsException>(index < mSize);
    return ((Type*)data())[index];
  }

template <typename Type>
  typename tamias::Vector<Type>::ConstReference tamias::Vector<Type>::operator [] ( sizetype index ) const
  {
    utilities::assert<OutOfBoundsException>(index < mSize);
    return ((Type*)data())[index];
  }

template <typename Type>
  typename tamias::Vector<Type>::Iterator tamias::Vector<Type>::begin()
  {
    return Iterator((Type*)data());
  }

template <typename Type>
  typename tamias::Vector<Type>::Iterator tamias::Vector<Type>::end()
  {
    return Iterator((Type*)((Type*)data() + mSize));
  }

template <typename Type>
  typename tamias::Vector<Type>::ConstIterator tamias::Vector<Type>::begin() const
  {
    return ConstIterator((Type*)data());
  }

template <typename Type>
  typename tamias::Vector<Type>::ConstIterator tamias::Vector<Type>::end() const
  {
    return ConstIterator((Type*)((Type*)data() + mSize));
  }

template <typename Type>
  typename tamias::Vector<Type>::ReverseIterator tamias::Vector<Type>::rbegin()
  {
    return ReverseIterator((Type*)data() + mSize - 1);
  }

template <typename Type>
  typename tamias::Vector<Type>::ReverseIterator tamias::Vector<Type>::rend()
  {
    return ReverseIterator((Type*)((Type*)data() - 1));
  }

template <typename Type>
  typename tamias::Vector<Type>::ConstReverseIterator tamias::Vector<Type>::rbegin() const
  {
    return ConstReverseIterator((Type*)data() + mSize - 1);
  }

template <typename Type>
  typename tamias::Vector<Type>::ConstReverseIterator tamias::Vector<Type>::rend() const
  {
    return ConstReverseIterator((Type*)((Type*)data() - 1));
  }

template <typename Type>
  void tamias::Vector<Type>::clear()
  {
    for (sizetype i = 0; i < mSize; i++)
      (*this)[i].~Type();
    mSize = 0;
    manualReserve(0);
  }

template <typename Type>
  void tamias::Vector<Type>::resize( sizetype newSize )
  {
    for (sizetype i = newSize; i < mSize; i++)
      (*this)[i].~Type();
    sizetype oldSize = mSize;
    mSize = newSize;
    manualReserve(mSize * sizeof(Type));
    for (sizetype i = oldSize; i < mSize; i++)
      new((Type*)data() + i) Type();
  }

template <typename Type>
  void tamias::Vector<Type>::pushBack( Type const& source )
  {
    autoReserveUp((mSize + 1) * sizeof(Type));
    new ((Type*)data() + mSize++) Type(source);
  }

template <typename Type>
  tamias::VectorCreator<Type>::VectorCreator() : result()
  {
  }

template <typename Type>
  tamias::VectorCreator<Type>::VectorCreator( Type const &value ) : result(1, value)
  {
  }

template <typename Type>
  tamias::VectorCreator<Type>::VectorCreator( VectorCreator const &creator ) : result(creator.result)
  {
  }

template <typename Type>
  tamias::VectorCreator<Type>& tamias::VectorCreator<Type>::operator = ( VectorCreator const &creator )
  {
    result = creator.result;
    return *this;
  }

template <typename Type>
  tamias::VectorCreator<Type>::~VectorCreator()
  {
  }

template <typename Type>
  tamias::VectorCreator<Type>& tamias::VectorCreator<Type>::operator () ( Type const &value )
  {
    result.pushBack(value);
    return *this;
  }

template <typename Type>
  tamias::VectorCreator<Type>& tamias::VectorCreator<Type>::operator << ( Type const &value )
  {
    result.pushBack(value);
    return *this;
  }

template <typename Type>
  tamias::VectorCreator<Type>::operator tamias::Vector<Type>() const
  {
    return result;
  }

