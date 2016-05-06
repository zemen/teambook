/*
 * This file [basic/iterator_implementation.h] is part of the “libtamias” library
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

/* template DefaultIterator */
template <typename IteratorType>
  tamias::hidden::DefaultIterator<IteratorType>::DefaultIterator( Pointer value ) : pointer(value)
  {
  }

template <typename IteratorType>
  tamias::hidden::DefaultIterator<IteratorType>::DefaultIterator( DefaultIterator const &source ) : pointer(source.pointer)
  {
  }

template <typename IteratorType>
  tamias::hidden::DefaultIterator<IteratorType>& tamias::hidden::DefaultIterator<IteratorType>::operator = ( DefaultIterator const &source )
  {
    pointer = source.pointer;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultIterator<IteratorType>::~DefaultIterator()
  {
  }

template <typename IteratorType>
  typename tamias::hidden::DefaultIterator<IteratorType>::Reference tamias::hidden::DefaultIterator<IteratorType>::operator * () const
  {
    return *pointer;
  }

template <typename IteratorType>
  typename tamias::hidden::DefaultIterator<IteratorType>::Pointer tamias::hidden::DefaultIterator<IteratorType>::operator -> () const
  {
    return pointer;
  }

template <typename IteratorType>
  typename tamias::hidden::DefaultIterator<IteratorType>::Reference tamias::hidden::DefaultIterator<IteratorType>::operator [] ( tamias::sizetype offset ) const
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
  tamias::hidden::DefaultIterator<IteratorType>& tamias::hidden::DefaultIterator<IteratorType>::operator += ( tamias::sizetype offset )
  {
    pointer += offset;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultIterator<IteratorType>& tamias::hidden::DefaultIterator<IteratorType>::operator -= ( tamias::sizetype offset )
  {
    pointer -= offset;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultIterator<IteratorType> tamias::hidden::DefaultIterator<IteratorType>::operator + ( tamias::sizetype value ) const
  {
    return DefaultIterator<IteratorType>(pointer + value);
  }

template <typename IteratorType>
  tamias::hidden::DefaultIterator<IteratorType> tamias::hidden::DefaultIterator<IteratorType>::operator - ( tamias::sizetype value ) const
  {
    return DefaultIterator<IteratorType>(pointer - value);
  }

template <typename IteratorType>
  tamias::sizetype tamias::hidden::DefaultIterator<IteratorType>::operator - ( DefaultIterator const &iterator ) const
  {
    return iterator.pointer - pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultIterator<IteratorType>::operator == ( DefaultIterator const &value ) const
  {
    return pointer == value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultIterator<IteratorType>::operator != ( DefaultIterator const &value ) const
  {
    return pointer != value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultIterator<IteratorType>::operator < ( DefaultIterator const &value ) const
  {
    return pointer < value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultIterator<IteratorType>::operator <= ( DefaultIterator const&value ) const
  {
    return pointer <= value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultIterator<IteratorType>::operator > ( DefaultIterator const &value ) const
  {
    return pointer > value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultIterator<IteratorType>::operator >= ( DefaultIterator const &value ) const
  {
    return pointer >= value.pointer;
  }


/* template DefaultConstIterator */
template <typename IteratorType>
  tamias::hidden::DefaultConstIterator<IteratorType>::DefaultConstIterator( ConstPointer value ) : pointer(value)
  {
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstIterator<IteratorType>::DefaultConstIterator( DefaultConstIterator const &source ) : pointer(source.pointer)
  {
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstIterator<IteratorType>& tamias::hidden::DefaultConstIterator<IteratorType>::operator = ( DefaultConstIterator const &source )
  {
    pointer = source.pointer;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstIterator<IteratorType>::~DefaultConstIterator()
  {
  }

template <typename IteratorType>
  typename tamias::hidden::DefaultConstIterator<IteratorType>::ConstReference tamias::hidden::DefaultConstIterator<IteratorType>::operator * () const
  {
    return *pointer;
  }

template <typename IteratorType>
  typename tamias::hidden::DefaultConstIterator<IteratorType>::ConstPointer tamias::hidden::DefaultConstIterator<IteratorType>::operator -> () const
  {
    return pointer;
  }

template <typename IteratorType>
  typename tamias::hidden::DefaultConstIterator<IteratorType>::ConstReference tamias::hidden::DefaultConstIterator<IteratorType>::operator [] ( tamias::sizetype offset ) const
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
  tamias::hidden::DefaultConstIterator<IteratorType>& tamias::hidden::DefaultConstIterator<IteratorType>::operator += ( tamias::sizetype offset )
  {
    pointer += offset;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstIterator<IteratorType>& tamias::hidden::DefaultConstIterator<IteratorType>::operator -= ( tamias::sizetype offset )
  {
    pointer -= offset;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstIterator<IteratorType> tamias::hidden::DefaultConstIterator<IteratorType>::operator + ( tamias::sizetype value ) const
  {
    return DefaultConstIterator<IteratorType>(pointer + value);
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstIterator<IteratorType> tamias::hidden::DefaultConstIterator<IteratorType>::operator - ( tamias::sizetype value ) const
  {
    return DefaultConstIterator<IteratorType>(pointer - value);
  }

template <typename IteratorType>
  tamias::sizetype tamias::hidden::DefaultConstIterator<IteratorType>::operator - ( DefaultConstIterator const &iterator ) const
  {
    return iterator.pointer - pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultConstIterator<IteratorType>::operator == ( DefaultConstIterator const &value ) const
  {
    return pointer == value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultConstIterator<IteratorType>::operator != ( DefaultConstIterator const &value ) const
  {
    return pointer != value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultConstIterator<IteratorType>::operator < ( DefaultConstIterator const &value ) const
  {
    return pointer < value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultConstIterator<IteratorType>::operator <= ( DefaultConstIterator const &value ) const
  {
    return pointer <= value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultConstIterator<IteratorType>::operator > ( DefaultConstIterator const &value ) const
  {
    return pointer > value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultConstIterator<IteratorType>::operator >= ( DefaultConstIterator const &value ) const
  {
    return pointer >= value.pointer;
  }


/* template DefaultReverseIterator */
template <typename IteratorType>
  tamias::hidden::DefaultReverseIterator<IteratorType>::DefaultReverseIterator( Pointer value ) : pointer(value)
  {
  }

template <typename IteratorType>
  tamias::hidden::DefaultReverseIterator<IteratorType>::DefaultReverseIterator( DefaultReverseIterator const &source ) : pointer(source.pointer)
  {
  }

template <typename IteratorType>
  tamias::hidden::DefaultReverseIterator<IteratorType>& tamias::hidden::DefaultReverseIterator<IteratorType>::operator = ( DefaultReverseIterator const &source )
  {
    pointer = source.pointer;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultReverseIterator<IteratorType>::~DefaultReverseIterator()
  {
  }

template <typename IteratorType>
  typename tamias::hidden::DefaultReverseIterator<IteratorType>::Reference tamias::hidden::DefaultReverseIterator<IteratorType>::operator * () const
  {
    return *pointer;
  }

template <typename IteratorType>
  typename tamias::hidden::DefaultReverseIterator<IteratorType>::Pointer tamias::hidden::DefaultReverseIterator<IteratorType>::operator -> () const
  {
    return pointer;
  }

template <typename IteratorType>
  typename tamias::hidden::DefaultReverseIterator<IteratorType>::Reference tamias::hidden::DefaultReverseIterator<IteratorType>::operator [] ( tamias::sizetype offset ) const
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
  tamias::hidden::DefaultReverseIterator<IteratorType> tamias::hidden::DefaultReverseIterator<IteratorType>::operator ++ ( int )
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
  tamias::hidden::DefaultReverseIterator<IteratorType> tamias::hidden::DefaultReverseIterator<IteratorType>::operator -- ( int )
  {
    return DefaultReverseIterator<IteratorType>(pointer++);
  }

template <typename IteratorType>
  tamias::hidden::DefaultReverseIterator<IteratorType>& tamias::hidden::DefaultReverseIterator<IteratorType>::operator += ( tamias::sizetype offset )
  {
    pointer -= offset;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultReverseIterator<IteratorType>& tamias::hidden::DefaultReverseIterator<IteratorType>::operator -= ( tamias::sizetype offset )
  {
    pointer += offset;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultReverseIterator<IteratorType> tamias::hidden::DefaultReverseIterator<IteratorType>::operator + ( tamias::sizetype value ) const
  {
    return DefaultReverseIterator<IteratorType>(pointer - value);
  }

template <typename IteratorType>
  tamias::hidden::DefaultReverseIterator<IteratorType> tamias::hidden::DefaultReverseIterator<IteratorType>::operator - ( tamias::sizetype value ) const
  {
    return DefaultReverseIterator<IteratorType>(pointer + value);
  }

template <typename IteratorType>
  tamias::sizetype tamias::hidden::DefaultReverseIterator<IteratorType>::operator - ( DefaultReverseIterator const &iterator ) const
  {
    return pointer - iterator.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultReverseIterator<IteratorType>::operator == ( DefaultReverseIterator const &value ) const
  {
    return pointer == value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultReverseIterator<IteratorType>::operator != ( DefaultReverseIterator const &value ) const
  {
    return pointer != value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultReverseIterator<IteratorType>::operator < ( DefaultReverseIterator const &value ) const
  {
    return pointer > value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultReverseIterator<IteratorType>::operator <= ( DefaultReverseIterator const &value ) const
  {
    return pointer >= value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultReverseIterator<IteratorType>::operator > ( DefaultReverseIterator const &value ) const
  {
    return pointer < value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultReverseIterator<IteratorType>::operator >= ( DefaultReverseIterator const &value ) const
  {
    return pointer <= value.pointer;
  }


/* template DefaultConstReverseIterator */
template <typename IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType>::DefaultConstReverseIterator( ConstPointer value ) : pointer(value)
  {
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType>::DefaultConstReverseIterator( DefaultConstReverseIterator const &source ) : pointer(source.pointer)
  {
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType>&
  tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator = ( DefaultConstReverseIterator const &source )
  {
    pointer = source.pointer;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType>::~DefaultConstReverseIterator()
  {
  }

template <typename IteratorType>
  typename tamias::hidden::DefaultConstReverseIterator<IteratorType>::ConstReference tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator * () const
  {
    return *pointer;
  }

template <typename IteratorType>
  typename tamias::hidden::DefaultConstReverseIterator<IteratorType>::ConstPointer tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator -> () const
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
  tamias::hidden::DefaultConstReverseIterator<IteratorType>& tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator ++ ()
  {
    --pointer;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType> tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator ++ ( int )
  {
    return DefaultConstReverseIterator<IteratorType>(pointer--);
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType>& tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator -- ()
  {
    ++pointer;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType> tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator -- ( int )
  {
    return DefaultConstReverseIterator<IteratorType>(pointer++);
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType>& tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator += ( tamias::sizetype offset )
  {
    pointer -= offset;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType>& tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator -= ( tamias::sizetype offset )
  {
    pointer += offset;
    return *this;
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType> tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator + ( tamias::sizetype value ) const
  {
    return DefaultReverseIterator<IteratorType>(pointer - value);
  }

template <typename IteratorType>
  tamias::hidden::DefaultConstReverseIterator<IteratorType> tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator - ( tamias::sizetype value ) const
  {
    return DefaultReverseIterator<IteratorType>(pointer + value);
  }

template <typename IteratorType>
  tamias::sizetype tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator - ( DefaultConstReverseIterator const &iterator ) const
  {
    return pointer - iterator.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator == ( DefaultConstReverseIterator const &value ) const
  {
    return pointer == value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator != ( DefaultConstReverseIterator const &value ) const
  {
    return pointer != value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator < ( DefaultConstReverseIterator const &value ) const
  {
    return pointer > value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator <= ( DefaultConstReverseIterator const &value ) const
  {
    return pointer >= value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator > ( DefaultConstReverseIterator const &value ) const
  {
    return pointer < value.pointer;
  }

template <typename IteratorType>
  bool tamias::hidden::DefaultConstReverseIterator<IteratorType>::operator >= ( DefaultConstReverseIterator const &value ) const
  {
    return pointer <= value.pointer;
  }

