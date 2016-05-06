/*
 * This file [baic/string.cpp] is part of the “libtamias” library
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

#include "../../include/basic/string.h"

using tamias::chartype;
using tamias::sizetype;
using tamias::ByteArray;
using tamias::String;

String::String() : AbstractData(), stringLength(0)
{
}

String::String( chartype source ) : AbstractData(sizeof(chartype)), stringLength(1)
{
  ((chartype*)data)[0] = source;
}

String::String( const chartype *source ) : AbstractData(), stringLength(0)
{
  while (source[stringLength] != '\0')
    stringLength++;
  manualReserve(stringLength * sizeof(chartype));
  for (sizetype i = 0; i < stringLength; i++)
    ((chartype*)data)[i] = source[i];
}

String::String( const chartype *source, sizetype sourceLength ) : AbstractData(sourceLength * sizeof(chartype)),
                                                                  stringLength(sourceLength)
{
  for (sizetype i = 0; i < stringLength; i++)
    ((chartype*)data)[i] = source[i];
}

String::String( const char *source ) : AbstractData(), stringLength(0)
{
  operator = (fromUtf8(ByteArray(source)));
}

String::String( const char *source, sizetype sourceLength ) : AbstractData(), stringLength(0)
{
  operator = (fromUtf8(ByteArray(source, sourceLength)));
}

String::String( const ByteArray &source ) : AbstractData(), stringLength(0)
{
  operator = (fromUtf8(source));
}

String::String( const String &source ) : AbstractData(source.stringLength * sizeof(chartype)),
                                         stringLength(source.stringLength)
{
  // TODO: use memoryCopy()
  for (sizetype i = 0; i < stringLength; i++)
    ((chartype*)data)[i] = ((chartype*)(source.data))[i];
}

String& String::operator = ( const String &source )
{
  manualReserve(source.stringLength * sizeof(chartype));
  stringLength = source.stringLength;
  for (sizetype i = 0; i < stringLength; i++)
    ((chartype*)data)[i] = ((chartype*)(source.data))[i];
  return *this;
}

String::~String()
{
  stringLength = 0;
}

// const String& String::operator = ( chartype source )
// {
//   manualReserve(sizeof(chartype)), stringLength = 1;
//   ((chartype*)data)[0] = source;
//   return *this;
// }

// const String& String::operator = ( const chartype *source )
// {
//   sizetype sourceLength = 0;
//   while (source[sourceLength] != '\0')
//     sourceLength++;
//   manualReserve(sourceLength * sizeof(chartype)), stringLength = sourceLength;
//   for (sizetype i = 0; i < sourceLength; i++)
//     ((chartype*)data)[i] = source[i];
//   return *this;
// }

// const String& String::operator = ( const char *source )
// {
//   return operator=(fromUtf8(source));
// }

// String String::fromUtf8( const char *source )
// {
//   sizetype sourceLength = 0;
//   while (source[sourceLength] != '\0')
//     sourceLength++;
//   return fromUtf8(source, sourceLength);
// }

String String::fromUtf8( const ByteArray &source )
{
  String result;
  for (sizetype i = 0; i < source.length(); i++)
    if ((source[i] & 0x80) == 0)
      result += (chartype)source[i];
    else if ((source[i] & 0x40) == 0)
      ; // TODO ?? may be throw exception
    else if ((source[i] & 0x20) == 0)
    {
      chartype first = source[i++];
      if (i >= source.length())
        break;
      chartype second = source[i];
      result += ((first & 0x1f) << 6) | (second & 0x3f);
    }
    else if ((source[i] & 0x10) == 0)
    {
      chartype first = source[i++];
      if (i >= source.length())
        break;
      chartype second = source[i++];
      if (i >= source.length())
        break;
      chartype third = source[i];
      result += ((first & 0x1f) << 12) | ((second & 0x3f) << 6) | (third & 0x3f);
    }
    else if ((source[i] & 0x8) == 0)
    {
      chartype first = source[i++];
      if (i >= source.length())
        break;
      chartype second = source[i++];
      if (i >= source.length())
        break;
      chartype third = source[i++];
      if (i >= source.length())
        break;
      chartype fourth = source[i];
      result += ((first & 0x1f) << 18) | ((second & 0x3f) << 12) | ((third & 0x3f) << 6) | (fourth & 0x3f);
    }
    else
      ;
  return result;
}

// String String::fromUtf8( const char *source, sizetype sourceLength )
// {
//   String result;
//   for (sizetype i = 0; i < sourceLength; i++)
//     if ((source[i] & 0x80) == 0)
//       result += (chartype)source[i];
//     else if ((source[i] & 0x40) == 0)
//       ; // TODO ?? may be throw exception
//     else if ((source[i] & 0x20) == 0)
//     {
//       chartype first = source[i++];
//       if (i >= sourceLength)
//         break;
//       chartype second = source[i];
//       result += ((first & 0x1f) << 6) | (second & 0x3f);
//     }
//     else if ((source[i] & 0x10) == 0)
//     {
//       chartype first = source[i++];
//       if (i >= sourceLength)
//         break;
//       chartype second = source[i++];
//       if (i >= sourceLength)
//         break;
//       chartype third = source[i];
//       result += ((first & 0x1f) << 12) | ((second & 0x3f) << 6) | (third & 0x3f);
//     }
//     else if ((source[i] & 0x8) == 0)
//     {
//       chartype first = source[i++];
//       if (i >= sourceLength)
//         break;
//       chartype second = source[i++];
//       if (i >= sourceLength)
//         break;
//       chartype third = source[i++];
//       if (i >= sourceLength)
//         break;
//       chartype fourth = source[i];
//       result += ((first & 0x1f) << 18) | ((second & 0x3f) << 12) | ((third & 0x3f) << 6) | (fourth & 0x3f);
//     }
//     else
//       ;
//   return result;
// }

// String String::fromUtf8( const ByteData &source )
// {
//   return fromUtf8(source.cString(), source.size());
// }

// const String& String::operator+=( chartype source )
// {
//   autoReserveUp((stringLength + 1) * sizeof(chartype));
//   ((chartype*)data)[stringLength++] = source;
//   return *this;
// }

// const String& String::operator+=( const chartype *source )
// {
//   return operator+=(String(source));
// }

// const String& String::operator+=( const char *source )
// {
//   return operator+=(fromUtf8(source));
// }

String& String::operator += ( const String &source )
{
  autoReserveUp((stringLength + source.stringLength) * sizeof(chartype));
  for (sizetype i = 0; i < source.stringLength; i++)
    ((chartype*)data)[stringLength + i] = ((chartype*)(source.data))[i];
  stringLength += source.stringLength;
  return *this;
}

// String String::operator + ( chartype source ) const
// {
//   String result(*this);
//   result += source;
//   return result;
// }

// String String::operator+( const chartype *source ) const
// {
//   String result(*this);
//   result += source;
//   return result;
// }

// String String::operator+( const char *source ) const
// {
//   String result(*this);
//   result += source;
//   return result;
// }

String String::operator + ( const String &source ) const
{
  String result(*this);
  result += source;
  return result;
}

sizetype String::length() const
{
  return stringLength;
}

sizetype String::size() const
{
  return stringLength * sizeof(chartype);
}

chartype String::operator [] ( sizetype index ) const
{
  return ((chartype*)data)[index];
}

chartype& String::operator [] ( sizetype index )
{
  return ((chartype*)data)[index];
}

String::Iterator String::begin()
{
  return Iterator((chartype*)data);
}

String::ConstIterator String::begin() const
{
  return ConstIterator((chartype*)data);
}

String::Iterator String::end()
{
  return Iterator((chartype*)data + stringLength);
}

String::ConstIterator String::end() const
{
  return ConstIterator((chartype*)data + stringLength);
}

String::ReverseIterator String::reverseBegin()
{
  return ReverseIterator((chartype*)data + stringLength - 1);
}

String::ConstReverseIterator String::reverseBegin() const
{
  return ConstReverseIterator((chartype*)data + stringLength - 1);
}

String::ReverseIterator String::reverseEnd()
{
  return ReverseIterator((chartype*)data - 1);
}

String::ConstReverseIterator String::reverseEnd() const
{
  return ConstReverseIterator((chartype*)data - 1);
}

// int String::compare( chartype source ) const
// {
//   if (stringLength == 0 || ((chartype*)data)[0] < source)
//     return -1;
//   else if (stringLength == 1 && ((chartype*)data)[0] == source)
//     return 0;
//   else
//     return 1;
// }

int String::compare( const chartype *source ) const
{
  sizetype i;
  for (i = 0; i < stringLength && source[i] != '\0'; i++)
    if (((chartype*)data)[i] != source[i])
      return ((chartype*)data)[i] < source[i] ? -1 : 1;
  return i < stringLength ? 1 : (source[i] != '\0' ? -1 : 0);
}

// int String::compare( const char *source ) const
// {
//   return compare(fromUtf8(source));
// }

int String::compare( const String &source ) const
{
  sizetype i;
  for (i = 0; i < stringLength && i < source.stringLength; i++)
    if (((chartype*)data)[i] != ((chartype*)(source.data))[i])
      return ((chartype*)data)[i] < source[i] ? -1 : 1;
  return i < stringLength ? 1 : (i < source.stringLength ? -1 : 0);
}

// sizetype String::find( chartype source ) const
// {
//   sizetype i;
//   for (i = 0; i < stringLength; i++)
//     if (((chartype*)data)[i] == source)
//       break;
//   return i;
// }

// sizetype String::find( const chartype *source ) const
// {
//   return find(String(source));
// }

// sizetype String::find( const char *source ) const
// {
//   return find(fromUtf8(source));
// }

sizetype String::find( const String &source ) const
{
  if (stringLength < source.stringLength)
    return stringLength;
  uinttype64 sourceHash = 0;
  uinttype64 hashPower = 1;
  uinttype64 targetHash = 0;
  for (sizetype i = 0; i < source.stringLength; i++)
  {
    sourceHash = sourceHash * 239017 + ((chartype*)(source.data))[i];
    hashPower *= 239017;
    targetHash = targetHash * 239017 + ((chartype*)data)[i];
  }
  for (sizetype i = 0; i + source.stringLength <= stringLength; i++)
  {
    if (targetHash == sourceHash)
    {
      bool equal = true;
      for (sizetype j = 0; j < source.stringLength; j++)
        if (((chartype*)data)[i + j] != ((chartype*)(source.data))[j])
        {
          equal = false;
          break;
        }
      if (equal)
        return i;
    }
    if (i + source.stringLength < stringLength)
      targetHash = targetHash * 239017 + ((chartype*)data)[i + source.stringLength] - hashPower * ((chartype*)data)[i] ;
  }
  return stringLength;
}

String String::subString( sizetype index, sizetype length ) const
{
  return String(((chartype*)data) + index, length);
}

ByteArray String::toUtf8() const
{
  ByteArray result;
  for (sizetype i = 0; i < stringLength; i++)
    if (((chartype*)data)[i] <= 0x7f)
      result += (char)((chartype*)data)[i];
    else if (((chartype*)data)[i] <= 0x7ff)
    {
      result += (char)((((chartype*)data)[i] >> 6) | 0xc0);
      result += (char)((((chartype*)data)[i] & 0x3f) | 0x80);
    }
    else if (((chartype*)data)[i] <= 0xffff)
    {
      result += (char)((((chartype*)data)[i] >> 12) | 0xe0);
      result += (char)(((((chartype*)data)[i] >> 6) & 0x3f) | 0x80);
      result += (char)((((chartype*)data)[i] & 0x3f) | 0x80);
    }
    else if (((chartype*)data)[i] <= 0x1fffff)
    {
      result += (char)((((chartype*)data)[i] >> 18) | 0xf0);
      result += (char)(((((chartype*)data)[i] >> 12) & 0x3f) | 0x80);
      result += (char)(((((chartype*)data)[i] >> 6) & 0x3f) | 0x80);
      result += (char)((((chartype*)data)[i] & 0x3f) | 0x80);
    }
    else
      ; // Sehr schlecht. TODO
  return result;
}

ByteArray String::toUtf16() const
// http://tools.ietf.org/html/rfc2781
{
  ByteArray result;
  for (sizetype i = 0; i < stringLength; i++)
    if (((chartype*)data)[i] <= 0xffff)
    {
      result += (char)(((chartype*)data)[i] & 0xff);
      result += (char)((((chartype*)data)[i] >> 8) & 0xff);
    }
    else if (((chartype*)data)[i] <= 0x10ffff)
    {
      chartype temp = ((chartype*)data)[i] - 0x10000;
      uinttype16 r1 = (temp & 0x3ff) + 0xd800;
      uinttype16 r2 = ((temp >> 10) & 0x3ff) + 0xdc00;
      result += (char)((r1 >> 8) & 0xff);
      result += (char)(r1 & 0xff);
      result += (char)((r2 >> 8) & 0xff);
      result += (char)(r2 & 0xff);
    }
  return result;
}

// bool String::operator<( chartype source ) const
// {
//   return compare(source) < 0;
// }

// bool String::operator<=( chartype source ) const
// {
//   return compare(source) <= 0;
// }

// bool String::operator>( chartype source ) const
// {
//   return compare(source) > 0;
// }

// bool String::operator>=( chartype source ) const
// {
//   return compare(source) >= 0;
// }

// bool String::operator==( chartype source ) const
// {
//   if (stringLength != 1)
//     return false;
//   return compare(source) == 0;
// }

// bool String::operator!=( chartype source ) const
// {
//   if (stringLength != 1)
//     return true;
//   return compare(source) != 0;
// }

// bool String::operator<( const chartype *source ) const
// {
//   return compare(source) < 0;
// }

bool String::operator <= ( const chartype *source ) const
{
  return compare(source) <= 0;
}

bool String::operator > ( const chartype *source ) const
{
  return compare(source) > 0;
}

bool String::operator >= ( const chartype *source ) const
{
  return compare(source) >= 0;
}

bool String::operator == ( const chartype *source ) const
{
  return compare(source) == 0;
}

bool String::operator != ( const chartype *source ) const
{
  return compare(source) != 0;
}

// bool String::operator <( const char *source ) const
// {
//   return compare(source) < 0;
// }

// bool String::operator<=( const char *source ) const
// {
//   return compare(source) <= 0;
// }

// bool String::operator>( const char *source ) const
// {
//   return compare(source) > 0;
// }

// bool String::operator>=( const char *source ) const
// {
//   return compare(source) >= 0;
// }

// bool String::operator==( const char *source ) const
// {
//   return compare(source) == 0;
// }

// bool String::operator!=( const char *source ) const
// {
//   return compare(source) != 0;
// }

bool String::operator < ( const String &source ) const
{
  return compare(source) < 0;
}

bool String::operator <= ( const String &source ) const
{
  return compare(source) <= 0;
}

bool String::operator > ( const String &source ) const
{
  return compare(source) > 0;
}

bool String::operator >= ( const String &source ) const
{
  return compare(source) >= 0;
}

bool String::operator == ( const String &source ) const
{
  if (stringLength != source.stringLength)
    return false;
  return compare(source) == 0;
}

bool String::operator != ( const String &source ) const
{
  if (stringLength != source.stringLength)
    return true;
  return compare(source) != 0;
}

String tamias::operator + ( chartype first, const String &second )
{
  String result(first);
  result += second;
  return result;
}

String tamias::operator + ( const chartype *first, const String &second )
{
  String result(first);
  result += second;
  return result;
}

String tamias::operator + ( const char *first, const String &second )
{
  String result(first);
  result += second;
  return result;
}

bool tamias::operator < ( chartype first, const String &second )
{
  return second.compare(first) > 0;
}

bool tamias::operator <= ( chartype first, const String &second )
{
  return second.compare(first) >= 0;
}

bool tamias::operator > ( chartype first, const String &second )
{
  return second.compare(first) < 0;
}

bool tamias::operator >= ( chartype first, const String &second )
{
  return second.compare(first) <= 0;
}

bool tamias::operator == ( chartype first, const String &second )
{
  if (second.length() != 1)
    return false;
  return second.compare(first) == 0;
}

bool tamias::operator != ( chartype first, const String &second )
{
  if (second.length() != 1)
    return true;
  return second.compare(first) != 0;
}

bool tamias::operator < ( const chartype *first, const String &second )
{
  return second.compare(first) > 0;
}

bool tamias::operator <= ( const chartype *first, const String &second )
{
  return second.compare(first) >= 0;
}

bool tamias::operator > ( const chartype *first, const String &second )
{
  return second.compare(first) < 0;
}

bool tamias::operator >= ( const chartype *first, const String &second )
{
  return second.compare(first) <= 0;
}

bool tamias::operator == ( const chartype *first, const String &second )
{
  return second.compare(first) == 0;
}

bool tamias::operator != ( const chartype *first, const String &second )
{
  return second.compare(first) != 0;
}

bool tamias::operator < ( const char *first, const String &second )
{
  return second.compare(first) > 0;
}

bool tamias::operator <= ( const char *first, const String &second )
{
  return second.compare(first) >= 0;
}

bool tamias::operator > ( const char *first, const String &second )
{
  return second.compare(first) < 0;
}

bool tamias::operator >= ( const char *first, const String &second )
{
  return second.compare(first) <= 0;
}

bool tamias::operator == ( const char *first, const String &second )
{
  return second.compare(first) == 0;
}

bool tamias::operator != ( const char *first, const String &second )
{
  return second.compare(first) != 0;
}

