/*
 * This file [main/vector.h] is part of the “libtamias” library
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

#ifndef _libtamias_main_vector_h_
#define _libtamias_main_vector_h_

#include <new>
#include "../basic/abstract_data.h"
#include "../basic/iterator.h"

namespace tamias
{
  template <typename Type>
    class Vector : private hidden::AbstractData
    {
      public:
        typedef Type* Pointer;
        typedef Type& Reference;
        typedef const Type* ConstPointer;
        typedef const Type& ConstReference;
        typedef hidden::DefaultIterator <Pointer> Iterator;
        typedef hidden::DefaultIterator <ConstPointer> ConstIterator;
        typedef hidden::DefaultReverseIterator <Pointer> ReverseIterator;
        typedef hidden::DefaultReverseIterator <ConstPointer> ConstReverseIterator;
      private:
        sizetype vectorSize;
      public:
        Vector();
        Vector( sizetype initialSize, const Type &value = Type() );
        Vector( const Vector <Type> &vector );
        ~Vector();
        Vector& operator = ( const Vector &vector );

        sizetype size() const;
        const Type& operator [] ( sizetype index ) const;
        Type& operator [] ( sizetype index );
        Iterator begin();
        ConstIterator begin() const;
        Iterator end();
        ConstIterator end() const;
        ReverseIterator rbegin();
        ConstReverseIterator rbegin() const;
        ReverseIterator rend();
        ConstReverseIterator rend() const;

        void clear();
        void resize( sizetype newSize );
        void pushBack( const Type& );
    };

  template <typename Type>
    class VectorCreator
    {
      private:
        Vector <Type> result;
      public:
        VectorCreator();
        VectorCreator( const Type &value );
        VectorCreator( const VectorCreator &creator );
        ~VectorCreator();
        VectorCreator& operator = ( const VectorCreator &creator );
        VectorCreator& operator () ( const Type &value );
        VectorCreator& operator << ( const Type &value );
        const Vector <Type>& operator () () const;
        Vector <Type>& operator () ();
        operator Vector <Type> () const;
    };
}

template <typename Type>
  tamias::Vector <Type> ::Vector() : tamias::hidden::AbstractData(0), vectorSize(0)
  {
  }

template <typename Type>
  tamias::Vector <Type> ::Vector( sizetype initialSize, const Type &value )
                        : tamias::hidden::AbstractData(initialSize * sizeof(Type)), vectorSize(initialSize)
  {
    for (sizetype i = 0; i < initialSize; i++)
      new ((Type*)data + i) Type(value);
  }

template <typename Type>
  tamias::Vector <Type> ::Vector( const Vector <Type> &vector )
                        : tamias::hidden::AbstractData(vector.vectorSize * sizeof(Type)), vectorSize(vector.vectorSize)
  {
    for (sizetype i = 0; i < vectorSize; i++)
      new ((Type*)data + i) Type(((Type*)vector.data)[i]);
  }

template <typename Type>
  tamias::Vector <Type> ::~Vector()
  {
    for (sizetype i = 0; i < vectorSize; i++)
      ((Type*)data)[i].~Type();
  }

template <typename Type>
  tamias::Vector <Type>& tamias::Vector <Type> ::operator = ( const Vector &vector )
  {
    for (sizetype i = 0; i < vectorSize; i++)
      ((Type*)data)[i].~Type();
    vectorSize = vector.vectorSize;
    manualReserve(vectorSize * sizeof(Type));
    for (sizetype i = 0; i < vectorSize; i++)
      new ((Type*)data + i) Type(((Type*)vector.data)[i]);
    return *this;
  }

template <typename Type>
  tamias::sizetype tamias::Vector<Type>::size() const
  {
    return vectorSize;
  }

template <typename Type>
  const Type& tamias::Vector <Type> ::operator [] ( sizetype index ) const
  {
    return ((Type*)data)[index];
  }

template <typename Type>
  Type& tamias::Vector <Type> ::operator [] ( const sizetype index )
  {
    return ((Type*)data)[index];
  }

template <typename Type>
  typename tamias::Vector <Type> ::Iterator tamias::Vector <Type> ::begin()
  {
    return Iterator((Type*)data);
  }

template <typename Type>
  typename tamias::Vector <Type> ::Iterator tamias::Vector <Type> ::end()
  {
    return Iterator((Type*)((Type*)data + vectorSize));
  }

template <typename Type>
  void tamias::Vector <Type> ::clear()
  {
    for (sizetype i = 0; i < vectorSize; i++)
      ((Type*)data)[i].~Type();
    vectorSize = 0;
    manualReserve(0);
  }

template <typename Type>
  void tamias::Vector <Type> ::resize( sizetype newSize )
  {
    for (sizetype i = newSize; i < vectorSize; i++)
      ((Type*)data)[i].~Type();
    sizetype oldSize = vectorSize;
    vectorSize = newSize;
    manualReserve(vectorSize * sizeof(Type));
    for (sizetype i = oldSize; i < vectorSize; i++)
      new((Type*)data + i) Type();
  }

template <typename Type>
  void tamias::Vector <Type> ::pushBack( const Type& source )
  {
    autoReserveUp((vectorSize + 1) * sizeof(Type));
    new ((Type*)data + vectorSize) Type(source);
    vectorSize++;
  }

template <typename Type>
  tamias::VectorCreator <Type> ::VectorCreator() : result()
  {
  }

template <typename Type>
  tamias::VectorCreator <Type> ::VectorCreator( const Type &value ) : result(1, value)
  {
  }

template <typename Type>
  tamias::VectorCreator <Type> ::VectorCreator( const VectorCreator &creator ) : result(creator.result)
  {
  }

template <typename Type>
  tamias::VectorCreator<Type>::~VectorCreator()
  {
  }

template <typename Type>
  tamias::VectorCreator <Type>& tamias::VectorCreator <Type> ::operator = ( const VectorCreator &creator )
  {
    result = creator.result;
    return *this;
  }

template <typename Type>
  tamias::VectorCreator <Type>& tamias::VectorCreator <Type> ::operator () ( const Type &value )
  {
    result.pushBack(value);
    return *this;
  }

template <typename Type>
  tamias::VectorCreator <Type>& tamias::VectorCreator <Type> ::operator << ( const Type &value )
  {
    result.pushBack(value);
    return *this;
  }

template <typename Type>
  const tamias::Vector <Type>& tamias::VectorCreator <Type> ::operator () () const
  {
    return result;
  }

template <typename Type>
  tamias::Vector <Type>& tamias::VectorCreator <Type> ::operator () ()
  {
    return result;
  }

template <typename Type>
  tamias::VectorCreator <Type> ::operator tamias::Vector <Type> () const
  {
    return result;
  }

#endif // _libtamias_main_vector_h_

