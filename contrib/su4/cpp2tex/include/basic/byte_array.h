/*
 * This file [basic/byte_array.h] is part of the “libtamias” library
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

#include "../basic/abstract_data.h"
#include "../basic/iterator.h"
#include "../basic/types.h"
#include "../basic/utilities.h"

namespace tamias
{
  /* class ByteArray stores some binary data, or string in generic 8-bit encoding */
  class ByteArray : private hidden::AbstractData
  {
    public:
      typedef tamias::hidden::DefaultIterator<char*> Iterator;
      typedef tamias::hidden::DefaultConstIterator<char*> ConstIterator;
      typedef tamias::hidden::DefaultReverseIterator<char*> ReverseIterator;
      typedef tamias::hidden::DefaultConstReverseIterator<char*> ConstReverseIterator;
    private:
      sizetype arraySize;
    public:
      ByteArray();
      ByteArray( char source );
      ByteArray( const char *source );
      ByteArray( const void *source, sizetype sourceSize );
      ByteArray( const ByteArray &source );
      ByteArray& operator = ( const ByteArray &source );
      ~ByteArray();
//       ByteArray& operator = ( char source );
//       ByteArray& operator = ( const char *source );

      template <typename Type>
        static ByteArray makeDump( const Type &source );

      ByteArray& operator += ( const ByteArray &source );
      ByteArray operator + ( const ByteArray &source ) const;

      sizetype size() const;
      sizetype length() const;
      char& operator [] ( sizetype index);
      char operator [] ( sizetype index) const;
      Iterator begin();
      ConstIterator begin() const;
      Iterator end();
      ConstIterator end() const;
      ReverseIterator reverseBegin();
      ConstReverseIterator reverseBegin() const;
      ReverseIterator reverseEnd();
      ConstReverseIterator reverseEnd() const;

      int compare( char source ) const;
      int compare( const char *source ) const;
      int compare( const ByteArray &source) const;
      sizetype find( char source ) const;
      sizetype find( const char *source ) const;
      sizetype find( const ByteArray &source ) const;
      ByteArray subString( sizetype index, sizetype size ) const;
      void write( void *target, sizetype size ) const;
      char* cString();
      const char* cString() const;

      bool operator < ( char source ) const;
      bool operator < ( const char *source ) const;
      bool operator < ( const ByteArray &source ) const;
      bool operator <= ( char source ) const;
      bool operator <= ( const char *source ) const;
      bool operator <= ( const ByteArray &source ) const;
      bool operator > ( char source ) const;
      bool operator > ( const char *source ) const;
      bool operator > ( const ByteArray &source ) const;
      bool operator >= ( char source ) const;
      bool operator >= ( const char *source ) const;
      bool operator >= ( const ByteArray &source ) const;
      bool operator == ( char source ) const;
      bool operator == ( const char *source ) const;
      bool operator == ( const ByteArray &source ) const;
      bool operator != ( char source ) const;
      bool operator != ( const char *source ) const;
      bool operator != ( const ByteArray &source ) const;
  };

  ByteArray operator + ( char first, const ByteArray &second );
  ByteArray operator + ( const char *first, const ByteArray &second );
  bool operator < ( char first, const ByteArray &second );
  bool operator < ( const char *first, const ByteArray &second );
  bool operator <= ( char first, const ByteArray &second );
  bool operator <= ( const char *first, const ByteArray &second );
  bool operator > ( char first, const ByteArray &second );
  bool operator > ( const char *first, const ByteArray &second );
  bool operator >= ( char first, const ByteArray &second );
  bool operator >= ( const char *first, const ByteArray &second );
  bool operator == ( char first, const ByteArray &second );
  bool operator == ( const char *first, const ByteArray &second );
  bool operator != ( char first, const ByteArray &second );
  bool operator != ( const char *first, const ByteArray &second );
}

template <typename Type>
  tamias::ByteArray tamias::ByteArray::makeDump( const Type &source )
  {
    return ByteArray(&source, sizeof(Type));
  }

