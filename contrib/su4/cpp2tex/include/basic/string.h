/*
 * This file [basic/string.h] is part of the “libtamias” library
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

#ifndef _libtamias_basic_string_h_
#define _libtamias_basic_string_h_

#include "../basic/abstract_data.h"
#include "../basic/byte_array.h"
#include "../basic/types.h"

namespace tamias
{
  /* UTF-32 string */
  /* by default, char* means string in UTF-8. Luckily, it is compatible with acsii */
  class String : private hidden::AbstractData
  {
    public:
      typedef tamias::hidden::DefaultIterator<chartype*> Iterator;
      typedef tamias::hidden::DefaultConstIterator<chartype*> ConstIterator;
      typedef tamias::hidden::DefaultReverseIterator<chartype*> ReverseIterator;
      typedef tamias::hidden::DefaultConstReverseIterator<chartype*> ConstReverseIterator;
    private:
      sizetype stringLength;
    public:
      String();
      String( chartype source );
      String( const chartype *source );
      String( const chartype *source, sizetype sourceLength );
      String( const char *source );
      String( const char *source, sizetype sourceLength );
      String( const ByteArray &source );
      String( const String &string );
      String& operator = ( const String &source );
      ~String();

//       static String fromUtf8( const char *source );
//       static String fromUtf8( const char *source, sizetype sourceLength );
      static String fromUtf8( const ByteArray &source );
// TODO:      ByteData operator()();

      String& operator += ( const String &source );
      String operator + ( const String &source ) const;

      sizetype length() const;
      sizetype size() const;
      chartype& operator [] ( sizetype index );
      chartype operator [] ( sizetype index ) const;
      Iterator begin();
      ConstIterator begin() const;
      Iterator end();
      ConstIterator end() const;
      ReverseIterator reverseBegin();
      ConstReverseIterator reverseBegin() const;
      ReverseIterator reverseEnd();
      ConstReverseIterator reverseEnd() const;

//       int compare( chartype source ) const;
      int compare( const chartype *source ) const;
      // TODO optimize for const char* and ByteArray
//       int compare( const char *source ) const;
      int compare( const String &source ) const;
//       sizetype find( chartype source ) const; // TODO: remove all finds but find( const String &source )?
//       sizetype find( const chartype *source ) const;
//       sizetype find( const char *source ) const;
        /* We use Rabin-Karp algorithm to find a substring. http://en.wikipedia.org/wiki/Rabin-Karp_string_search_algorithm */
      sizetype find( const String &source ) const;
      String subString( sizetype start, sizetype length ) const;
      ByteArray toUtf8() const; // returns UTF-8 interpretation of string
      ByteArray toUtf16() const; // return UTF-16 interpretation of string

//       bool operator < ( chartype source ) const;
//       bool operator <= ( chartype source ) const;
//       bool operator > ( chartype source ) const;
//       bool operator >= ( chartype source ) const;
//       bool operator == ( chartype source ) const;
//       bool operator != ( chartype source ) const;
      bool operator < ( const chartype *source ) const;
      bool operator <= ( const chartype *source ) const;
      bool operator > ( const chartype *source ) const;
      bool operator >= ( const chartype *source ) const;
      bool operator == ( const chartype *source ) const;
      bool operator != ( const chartype *source ) const;
//       bool operator < ( const char *source ) const;
//       bool operator <= ( const char *source ) const;
//       bool operator > ( const char *source ) const;
//       bool operator >= ( const char *source ) const;
//       bool operator == ( const char *source ) const;
//       bool operator != ( const char *source ) const;
      bool operator < ( const String &source ) const;
      bool operator <= ( const String &source ) const;
      bool operator > ( const String &source ) const;
      bool operator >= ( const String &source ) const;
      bool operator == ( const String &source ) const;
      bool operator != ( const String &source ) const;
  };
  String operator + ( chartype first, const String &second );
  String operator + ( const chartype *first, const String &second );
  String operator + ( const char *first, const String &second );
  bool operator < ( chartype first, const String &second );
  bool operator <= ( chartype first, const String &second );
  bool operator > ( chartype first, const String &second );
  bool operator >= ( chartype first, const String &second );
  bool operator == ( chartype first, const String &second );
  bool operator != ( chartype first, const String &second );
  bool operator < ( const chartype *fist, const String &second );
  bool operator <= ( const chartype *fist, const String &second );
  bool operator > ( const chartype *fist, const String &second );
  bool operator >= ( const chartype *fist, const String &second );
  bool operator == ( const chartype *fist, const String &second );
  bool operator != ( const chartype *fist, const String &second );
  bool operator < ( const char *fist, const String &second );
  bool operator <= ( const char *fist, const String &second );
  bool operator > ( const char *fist, const String &second );
  bool operator >= ( const char *fist, const String &second );
  bool operator == ( const char *fist, const String &second );
  bool operator != ( const char *fist, const String &second );
}

#endif // _libtamias_basic_string_h_

