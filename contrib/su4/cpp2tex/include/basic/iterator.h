/*
 * This file [basic/iterator.h] is part of the “libtamias” library
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

#ifndef _libtamias_basic_iterator_h
#define _libtamias_basic_iterator_h

#include <cstdlib>
#include "../basic/types.h"

namespace tamias
{
  namespace hidden
  {
    template <typename IteratorType>
      class IteratorTypes
      {
        public:
          typedef typename IteratorType::ValueType ValueType;
          typedef typename IteratorType::Pointer Pointer;
          typedef typename IteratorType::Reference Reference;
          typedef typename IteratorType::ConstPointer ConstPointer;
          typedef typename IteratorType::ConstReference ConstReference;
      };

    template <typename Type>
      class IteratorTypes <Type*>
      {
        public:
          typedef Type ValueType;
          typedef Type* Pointer;
          typedef Type& Reference;
          typedef const Type* ConstPointer;
          typedef const Type& ConstReference;
      };

    template <typename IteratorType>
      class DefaultIterator
      {
        public:
          typedef typename IteratorTypes<IteratorType>::ValueType ValueType;
          typedef typename IteratorTypes<IteratorType>::Pointer Pointer;
          typedef typename IteratorTypes<IteratorType>::Reference Reference;
          typedef typename IteratorTypes<IteratorType>::ConstPointer ConstPointer;
          typedef typename IteratorTypes<IteratorType>::ConstReference ConstReference;
        private:
          Pointer pointer;
        public:
          DefaultIterator( Pointer value = NULL );
          DefaultIterator( const DefaultIterator &iterator );
          ~DefaultIterator();
          DefaultIterator<IteratorType>& operator = ( const DefaultIterator &iterator );

          Reference operator * () const;
          Pointer operator -> () const;
          Reference operator [] ( sizetype offset ) const;

          DefaultIterator& operator ++ ();
          DefaultIterator operator ++ ( int );
          DefaultIterator& operator -- ();
          DefaultIterator operator -- ( int );

          DefaultIterator& operator += ( sizetype offset );
          DefaultIterator& operator -= ( sizetype offset );
          DefaultIterator operator + ( sizetype offset ) const;
          DefaultIterator operator - ( sizetype offset ) const;

          bool operator == ( const DefaultIterator &second ) const;
          bool operator != ( const DefaultIterator &second ) const;
          bool operator < ( const DefaultIterator &second ) const;
          bool operator <= ( const DefaultIterator &second ) const;
          bool operator > ( const DefaultIterator &second ) const;
          bool operator >= ( const DefaultIterator &second ) const;
      };

    template <typename IteratorType>
      class DefaultConstIterator
      {
        public:
          typedef typename IteratorTypes<IteratorType>::ValueType ValueType;
          typedef typename IteratorTypes<IteratorType>::Pointer Pointer;
          typedef typename IteratorTypes<IteratorType>::Reference Reference;
          typedef typename IteratorTypes<IteratorType>::ConstPointer ConstPointer;
          typedef typename IteratorTypes<IteratorType>::ConstReference ConstReference;
        private:
          ConstPointer pointer;
        public:
          DefaultConstIterator( ConstPointer value = NULL );
          DefaultConstIterator( const DefaultConstIterator &iterator );
          ~DefaultConstIterator();
          DefaultConstIterator<IteratorType>& operator = ( const DefaultConstIterator &iterator );

          ConstReference operator * () const;
          ConstPointer operator -> () const;
          ConstReference operator [] ( sizetype offset ) const;

          DefaultConstIterator& operator ++ ();
          DefaultConstIterator operator ++ ( int );
          DefaultConstIterator& operator -- ();
          DefaultConstIterator operator -- ( int );

          DefaultConstIterator& operator += ( sizetype offset );
          DefaultConstIterator& operator -= ( sizetype offset );
          DefaultConstIterator operator + ( sizetype offset ) const;
          DefaultConstIterator operator - ( sizetype offset ) const;

          bool operator == ( const DefaultConstIterator &second ) const;
          bool operator != ( const DefaultConstIterator &second ) const;
          bool operator < ( const DefaultConstIterator &second ) const;
          bool operator <= ( const DefaultConstIterator &second ) const;
          bool operator > ( const DefaultConstIterator &second ) const;
          bool operator >= ( const DefaultConstIterator &second ) const;
      };

    template <typename IteratorType>
      class DefaultReverseIterator
      {
        public:
          typedef typename IteratorTypes<IteratorType>::ValueType ValueType;
          typedef typename IteratorTypes<IteratorType>::Pointer Pointer;
          typedef typename IteratorTypes<IteratorType>::Reference Reference;
          typedef typename IteratorTypes<IteratorType>::ConstPointer ConstPointer;
          typedef typename IteratorTypes<IteratorType>::ConstReference ConstReference;
        private:
          Pointer pointer;
        public:
          DefaultReverseIterator( Pointer value = NULL );
          DefaultReverseIterator( const DefaultReverseIterator &iterator );
          ~DefaultReverseIterator();
          DefaultReverseIterator<IteratorType>& operator = ( const DefaultReverseIterator &iterator );

          Reference operator * () const;
          Pointer operator -> () const;
          Reference operator [] ( sizetype offset ) const;

          DefaultReverseIterator& operator ++ ();
          DefaultReverseIterator operator ++ ( int );
          DefaultReverseIterator& operator -- ();
          DefaultReverseIterator operator -- ( int );

          DefaultReverseIterator& operator += ( sizetype offset );
          DefaultReverseIterator& operator -= ( sizetype offset );
          DefaultReverseIterator operator + ( sizetype offset ) const;
          DefaultReverseIterator operator - ( sizetype offset ) const;

          bool operator == ( const DefaultReverseIterator &second ) const;
          bool operator != ( const DefaultReverseIterator &second ) const;
          bool operator < ( const DefaultReverseIterator &second ) const;
          bool operator <= ( const DefaultReverseIterator &second ) const;
          bool operator > ( const DefaultReverseIterator &second ) const;
          bool operator >= ( const DefaultReverseIterator &second ) const;
      };

    template <typename IteratorType>
      class DefaultConstReverseIterator
      {
        public:
          typedef typename IteratorTypes<IteratorType>::ValueType ValueType;
          typedef typename IteratorTypes<IteratorType>::Pointer Pointer;
          typedef typename IteratorTypes<IteratorType>::Reference Reference;
          typedef typename IteratorTypes<IteratorType>::ConstPointer ConstPointer;
          typedef typename IteratorTypes<IteratorType>::ConstReference ConstReference;
        private:
          ConstPointer pointer;
        public:
          DefaultConstReverseIterator( ConstPointer value = NULL );
          DefaultConstReverseIterator( const DefaultConstReverseIterator &iterator );
          ~DefaultConstReverseIterator();
          DefaultConstReverseIterator<IteratorType>& operator = ( const DefaultConstReverseIterator &iterator );

          ConstReference operator * () const;
          ConstPointer operator -> () const;
          ConstReference operator [] ( sizetype offset ) const;

          DefaultConstReverseIterator& operator ++ ();
          DefaultConstReverseIterator operator ++ ( int );
          DefaultConstReverseIterator& operator -- ();
          DefaultConstReverseIterator operator -- ( int );

          DefaultConstReverseIterator& operator += ( sizetype offset );
          DefaultConstReverseIterator& operator -= ( sizetype offset );
          DefaultConstReverseIterator operator + ( sizetype offset ) const;
          DefaultConstReverseIterator operator - ( sizetype offset ) const;

          bool operator == ( const DefaultConstReverseIterator &second ) const;
          bool operator != ( const DefaultConstReverseIterator &second ) const;
          bool operator < ( const DefaultConstReverseIterator &second ) const;
          bool operator <= ( const DefaultConstReverseIterator &second ) const;
          bool operator > ( const DefaultConstReverseIterator &second ) const;
          bool operator >= ( const DefaultConstReverseIterator &second ) const;
      };
  }
}

/* template DefaultIterator */
template <typename IteratorType>
  tamias::hidden::DefaultIterator<IteratorType>::DefaultIterator( Pointer value ) : pointer(value)
  {
  }

template <typename IteratorType>
  tamias::hidden::DefaultIterator<IteratorType>::DefaultIterator( const DefaultIterator &source ) : pointer(source.pointer)
  {
  }

template <typename IteratorType>
  tamias::hidden::DefaultIterator<IteratorType>::~DefaultIterator()
  {
  }

template <typename IteratorType>
  tamias::hidden::DefaultIterator<IteratorType>&
  tamias::hidden::DefaultIterator<IteratorType>::operator = ( const DefaultIterator &source )
  {
    pointer = source.pointer;
    return *this;
  }

template <typename IteratorType>
  typename tamias::hidden::DefaultIterator<IteratorType>::Reference
           tamias::hidden::DefaultIterator<IteratorType>::operator * () const
  {
    return *pointer;
  }

template <typename IteratorType>
  typename tamias::hidden::DefaultIterator<IteratorType>::Pointer
           tamias::hidden::DefaultIterator<IteratorType>::operator -> () const
  {
    return pointer;
  }

template <typename IteratorType>
  typename tamias::hidden::DefaultIterator<IteratorType>::Reference
           tamias::hidden::DefaultIterator<IteratorType>::operator [] ( tamias::sizetype offset ) const
  {
    return *(pointer + offset);
  }

template <typename IteratorType>
  tamias::hidden::DefaultIterator<IteratorType>& tamias::hidden::DefaultIterator<IteratorType>::operator ++ ()
  {
    ++pointer;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultIterator<IteratorType> tamias::hidden::DefaultIterator<IteratorType>::operator ++ ( int )
  {
    return DefaultIterator<IteratorType>(pointer++);
  }

template <typename IteratorType>
  tamias::hidden::DefaultIterator<IteratorType>& tamias::hidden::DefaultIterator<IteratorType>::operator -- ()
  {
    --pointer;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultIterator<IteratorType> tamias::hidden::DefaultIterator<IteratorType>::operator -- ( int )
  {
    return DefaultIterator<IteratorType>(pointer--);
  }

template <typename IteratorType>
  tamias::hidden::DefaultIterator<IteratorType>&
  tamias::hidden::DefaultIterator<IteratorType>::operator += ( tamias::sizetype offset )
  {
    pointer += offset;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultIterator<IteratorType>&
  tamias::hidden::DefaultIterator<IteratorType>::operator -= ( tamias::sizetype offset )
  {
    pointer -= offset;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultIterator<IteratorType>
  tamias::hidden::DefaultIterator<IteratorType>::operator + ( tamias::sizetype value ) const
  {
    return DefaultIterator<IteratorType>(pointer + value);
  }

template <typename IteratorType>
  tamias::hidden::DefaultIterator<IteratorType>
  tamias::hidden::DefaultIterator<IteratorType>::operator - ( tamias::sizetype value ) const
  {
    return DefaultIterator<IteratorType>(pointer - value);
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultIterator<IteratorType>::operator == ( const DefaultIterator& value ) const
  {
    return pointer == value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultIterator<IteratorType>::operator != ( const DefaultIterator& value ) const
  {
    return pointer != value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultIterator<IteratorType>::operator < ( const DefaultIterator& value ) const
  {
    return pointer < value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultIterator<IteratorType>::operator <= ( const DefaultIterator& value ) const
  {
    return pointer <= value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultIterator<IteratorType>::operator > ( const DefaultIterator& value ) const
  {
    return pointer > value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultIterator<IteratorType>::operator >= ( const DefaultIterator& value ) const
  {
    return pointer >= value.pointer;
  }

/* template DefaultConstIterator */
template <typename IteratorType>
  tamias::hidden::DefaultConstIterator<IteratorType>::DefaultConstIterator( ConstPointer value ) : pointer(value)
  {
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstIterator<IteratorType>::DefaultConstIterator( const DefaultConstIterator &source )
                : pointer(source.pointer)
  {
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstIterator<IteratorType>::~DefaultConstIterator()
  {
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstIterator<IteratorType>&
  tamias::hidden::DefaultConstIterator<IteratorType>::operator = ( const DefaultConstIterator &source )
  {
    pointer = source.pointer;
    return *this;
  }

template <typename IteratorType>
  typename tamias::hidden::DefaultConstIterator<IteratorType>::ConstReference
           tamias::hidden::DefaultConstIterator<IteratorType>::operator * () const
  {
    return *pointer;
  }

template <typename IteratorType>
  typename tamias::hidden::DefaultConstIterator<IteratorType>::ConstPointer
           tamias::hidden::DefaultConstIterator<IteratorType>::operator -> () const
  {
    return pointer;
  }

template <typename IteratorType>
  typename tamias::hidden::DefaultConstIterator<IteratorType>::ConstReference
           tamias::hidden::DefaultConstIterator<IteratorType>::operator [] ( tamias::sizetype offset ) const
  {
    return *(pointer + offset);
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstIterator<IteratorType>& tamias::hidden::DefaultConstIterator<IteratorType>::operator ++ ()
  {
    ++pointer;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstIterator<IteratorType> tamias::hidden::DefaultConstIterator<IteratorType>::operator ++ ( int )
  {
    return DefaultConstIterator<IteratorType>(pointer++);
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstIterator<IteratorType>& tamias::hidden::DefaultConstIterator<IteratorType>::operator -- ()
  {
    --pointer;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstIterator<IteratorType> tamias::hidden::DefaultConstIterator<IteratorType>::operator -- ( int )
  {
    return DefaultIterator<IteratorType>(pointer--);
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstIterator<IteratorType>&
  tamias::hidden::DefaultConstIterator<IteratorType>::operator += ( tamias::sizetype offset )
  {
    pointer += offset;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstIterator<IteratorType>&
  tamias::hidden::DefaultConstIterator<IteratorType>::operator -= ( tamias::sizetype offset )
  {
    pointer -= offset;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstIterator<IteratorType>
  tamias::hidden::DefaultConstIterator<IteratorType>::operator + ( tamias::sizetype value ) const
  {
    return DefaultConstIterator<IteratorType>(pointer + value);
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstIterator<IteratorType>
  tamias::hidden::DefaultConstIterator<IteratorType>::operator - ( tamias::sizetype value ) const
  {
    return DefaultConstIterator<IteratorType>(pointer - value);
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultConstIterator<IteratorType>::operator == ( const DefaultConstIterator& value ) const
  {
    return pointer == value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultConstIterator<IteratorType>::operator != ( const DefaultConstIterator& value ) const
  {
    return pointer != value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultConstIterator<IteratorType>::operator < ( const DefaultConstIterator& value ) const
  {
    return pointer < value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultConstIterator<IteratorType>::operator <= ( const DefaultConstIterator& value ) const
  {
    return pointer <= value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultConstIterator<IteratorType>::operator > ( const DefaultConstIterator& value ) const
  {
    return pointer > value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultConstIterator<IteratorType>::operator >= ( const DefaultConstIterator& value ) const
  {
    return pointer >= value.pointer;
  }

/* template DefaultReverseIterator */
template <typename IteratorType>
  tamias::hidden::DefaultReverseIterator<IteratorType>::DefaultReverseIterator( Pointer value ) : pointer(value)
  {
  }

template <typename IteratorType>
  tamias::hidden::DefaultReverseIterator<IteratorType>::DefaultReverseIterator( const DefaultReverseIterator &source )
                : pointer(source.pointer)
  {
  }

template <typename IteratorType>
  tamias::hidden::DefaultReverseIterator<IteratorType>::~DefaultReverseIterator()
  {
  }

template <typename IteratorType>
  tamias::hidden::DefaultReverseIterator<IteratorType>&
  tamias::hidden::DefaultReverseIterator<IteratorType>::operator = ( const DefaultReverseIterator &source )
  {
    pointer = source.pointer;
    return *this;
  }

template <typename IteratorType>
  typename tamias::hidden::DefaultReverseIterator<IteratorType>::Reference
           tamias::hidden::DefaultReverseIterator<IteratorType>::operator * () const
  {
    return *pointer;
  }

template <typename IteratorType>
  typename tamias::hidden::DefaultReverseIterator<IteratorType>::Pointer
           tamias::hidden::DefaultReverseIterator<IteratorType>::operator -> () const
  {
    return pointer;
  }

template <typename IteratorType>
  typename tamias::hidden::DefaultReverseIterator<IteratorType>::Reference
           tamias::hidden::DefaultReverseIterator<IteratorType>::operator [] ( tamias::sizetype offset ) const
  {
    return *(pointer - offset);
  }

template <typename IteratorType>
  tamias::hidden::DefaultReverseIterator<IteratorType>& tamias::hidden::DefaultReverseIterator<IteratorType>::operator ++ ()
  {
    --pointer;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultReverseIterator<IteratorType>
  tamias::hidden::DefaultReverseIterator<IteratorType>::operator ++ ( int )
  {
    return DefaultReverseIterator<IteratorType>(pointer--);
  }

template <typename IteratorType>
  tamias::hidden::DefaultReverseIterator<IteratorType>& tamias::hidden::DefaultReverseIterator<IteratorType>::operator -- ()
  {
    ++pointer;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultReverseIterator<IteratorType>
  tamias::hidden::DefaultReverseIterator<IteratorType>::operator -- ( int )
  {
    return DefaultReverseIterator<IteratorType>(pointer++);
  }

template <typename IteratorType>
  tamias::hidden::DefaultReverseIterator<IteratorType>&
  tamias::hidden::DefaultReverseIterator<IteratorType>::operator += ( tamias::sizetype offset )
  {
    pointer -= offset;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultReverseIterator<IteratorType>&
  tamias::hidden::DefaultReverseIterator<IteratorType>::operator -= ( tamias::sizetype offset )
  {
    pointer += offset;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultReverseIterator<IteratorType>
  tamias::hidden::DefaultReverseIterator<IteratorType>::operator + ( tamias::sizetype value ) const
  {
    return DefaultReverseIterator<IteratorType>(pointer - value);
  }

template <typename IteratorType>
  tamias::hidden::DefaultReverseIterator<IteratorType>
  tamias::hidden::DefaultReverseIterator<IteratorType>::operator - ( tamias::sizetype value ) const
  {
    return DefaultReverseIterator<IteratorType>(pointer + value);
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultReverseIterator<IteratorType>::operator == ( const DefaultReverseIterator& value ) const
  {
    return pointer == value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultReverseIterator<IteratorType>::operator != ( const DefaultReverseIterator& value ) const
  {
    return pointer != value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultReverseIterator<IteratorType>::operator < ( const DefaultReverseIterator& value ) const
  {
    return pointer > value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultReverseIterator<IteratorType>::operator <= ( const DefaultReverseIterator& value ) const
  {
    return pointer >= value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultReverseIterator<IteratorType>::operator > ( const DefaultReverseIterator& value ) const
  {
    return pointer < value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultReverseIterator<IteratorType>::operator >= ( const DefaultReverseIterator& value ) const
  {
    return pointer <= value.pointer;
  }

/* template DefaultConstReverseIterator */
template <typename IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType>::DefaultConstReverseIterator( ConstPointer value )
                : pointer(value)
  {
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType>
                ::DefaultConstReverseIterator( const DefaultConstReverseIterator &source ) : pointer(source.pointer)
  {
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType>::~DefaultConstReverseIterator()
  {
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType>&
  tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator = ( const DefaultConstReverseIterator &source )
  {
    pointer = source.pointer;
    return *this;
  }

template <typename IteratorType>
  typename tamias::hidden::DefaultConstReverseIterator<IteratorType>::ConstReference
           tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator * () const
  {
    return *pointer;
  }

template <typename IteratorType>
  typename tamias::hidden::DefaultConstReverseIterator<IteratorType>::ConstPointer
           tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator -> () const
  {
    return pointer;
  }

template <typename IteratorType>
  typename tamias::hidden::DefaultConstReverseIterator<IteratorType>::ConstReference
           tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator [] ( tamias::sizetype offset ) const
  {
    return *(pointer - offset);
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType>&
  tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator ++ ()
  {
    --pointer;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator ++ ( int )
  {
    return DefaultConstReverseIterator<IteratorType>(pointer--);
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType>&
  tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator -- ()
  {
    ++pointer;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator -- ( int )
  {
    return DefaultConstReverseIterator<IteratorType>(pointer++);
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType>&
  tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator += ( tamias::sizetype offset )
  {
    pointer -= offset;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType>&
  tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator -= ( tamias::sizetype offset )
  {
    pointer += offset;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator + ( tamias::sizetype value ) const
  {
    return DefaultConstReverseIterator<IteratorType>(pointer - value);
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator - ( tamias::sizetype value ) const
  {
    return DefaultConstReverseIterator<IteratorType>(pointer + value);
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultConstReverseIterator<IteratorType>
                     ::operator == ( const DefaultConstReverseIterator& value ) const
  {
    return pointer == value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultConstReverseIterator<IteratorType>
                     ::operator != ( const DefaultConstReverseIterator& value ) const
  {
    return pointer != value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultConstReverseIterator<IteratorType>
                     ::operator < ( const DefaultConstReverseIterator& value ) const
  {
    return pointer > value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultConstReverseIterator<IteratorType>
                     ::operator <= ( const DefaultConstReverseIterator& value ) const
  {
    return pointer >= value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultConstReverseIterator<IteratorType>
                     ::operator > ( const DefaultConstReverseIterator& value ) const
  {
    return pointer < value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultConstReverseIterator<IteratorType>
                     ::operator >= ( const DefaultConstReverseIterator& value ) const
  {
    return pointer <= value.pointer;
  }

#endif /* _libtamias_basic_iterator_h */

