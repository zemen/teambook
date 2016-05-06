/*
 * This file [basic/byte_array.cpp] is part of the “libtamias” library
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

#include "../../include/basic/byte_array.h"

using tamias::sizetype;
using tamias::utilities::memoryCopy;
using tamias::ByteArray;

ByteArray::ByteArray() : AbstractData(1), arraySize(0)
{
  ((char*)data)[0] = '\0';
}

ByteArray::ByteArray( char source ) : AbstractData(2), arraySize(1)
{
  ((char*)data)[0] = source;
  ((char*)data)[1] = '\0';
}

ByteArray::ByteArray( const char *source ) : AbstractData(), arraySize(0)
{
  for (arraySize = 0; source[arraySize] != '\0'; arraySize++)
    ;
  manualReserve(arraySize + 1);
  memoryCopy(data, source, arraySize + 1);
}

ByteArray::ByteArray( const void *source, sizetype size ) : AbstractData(size + 1), arraySize(size)
{
  memoryCopy(data, source, size);
  ((char*)data)[size] = '\0';
}

ByteArray::ByteArray( const ByteArray &source ) : AbstractData(source.arraySize + 1), arraySize(source.arraySize)
{
  memoryCopy(data, source.data, arraySize + 1);
}

ByteArray::~ByteArray()
{
  arraySize = 0;
}

// ByteArray& ByteArray::operator = ( char source )
// {
//   manualReserve(2);
//   arraySize = 1;
//   ((char*)data)[0] = source;
//   ((char*)data)[1] = '\0';
//   return *this;
// }

// ByteArray& ByteArray::operator = ( const char *source )
// {
//   for (arraySize = 0; source[arraySize] != '\0'; arraySize++)
//     ;
//   manualReserve(arraySize + 1);
//   memoryCopy(data, source, arraySize + 1);
//   return *this;
// }

ByteArray& ByteArray::operator = ( const ByteArray &source )
{
  manualReserve(source.arraySize + 1);
  arraySize = source.arraySize;
  memoryCopy(data, source.data, arraySize + 1);
  return *this;
}

// ByteArray& ByteArray::operator += ( char source )
// {
//   autoReserveUp(arraySize + 2);
//   ((char*)data)[arraySize++] = source;
//   ((char*)data)[arraySize] = '\0';
//   return *this;
// }

// ByteArray& ByteArray::operator += ( const char *source )
// {
//   return operator += (ByteArray(source));
// }

ByteArray& ByteArray::operator += ( const ByteArray &source )
{
  autoReserveUp(arraySize + source.arraySize + 1);
  memoryCopy((char*)data + arraySize, source.data, source.arraySize + 1);
  arraySize += source.arraySize;
  return *this;
}

// ByteArray ByteArray::operator + ( char source )
// {
//   ByteArray result(*this);
//   result += source;
//   return result;
// }

// ByteArray ByteArray::operator + ( const char *source )
// {
//   ByteArray result(*this);
//   result += source;
//   return result;
// }

ByteArray ByteArray::operator + ( const ByteArray &source ) const
{
  ByteArray result(*this);
  result += source;
  return result;
}

sizetype ByteArray::size() const
{
  return arraySize;
}

sizetype ByteArray::length() const
{
  return arraySize;
}

char& ByteArray::operator[]( sizetype index )
{
  // TODO: out-of-bounds check?
  return ((char*)data)[index];
}

char ByteArray::operator[]( sizetype index ) const
{
  // TODO: out-of-bounds check?
  return ((char*)data)[index];
}

ByteArray::Iterator ByteArray::begin()
{
  return Iterator((char*)data);
}

ByteArray::ConstIterator ByteArray::begin() const
{
  return ConstIterator((char*)data);
}

ByteArray::Iterator ByteArray::end()
{
  return Iterator((char*)data + arraySize);
}

ByteArray::ConstIterator ByteArray::end() const
{
  return ConstIterator((char*)data + arraySize);
}

ByteArray::ReverseIterator ByteArray::reverseBegin()
{
  return ReverseIterator((char*)data + arraySize - 1);
}

ByteArray::ConstReverseIterator ByteArray::reverseBegin() const
{
  return ConstReverseIterator((char*)data + arraySize - 1);
}

ByteArray::ReverseIterator ByteArray::reverseEnd()
{
  return ReverseIterator((char*)data - 1);
}

ByteArray::ConstReverseIterator ByteArray::reverseEnd() const
{
  return ConstReverseIterator((char*)data - 1);
}

int ByteArray::compare( char source ) const
{
  // TODO: seems that ascii octets (0..127) are higher that non-ascii (128-255)
  if (arraySize == 0)
    return -1;
  if (arraySize != 1 || ((char*)data)[0] != source)
    return ((char*)data)[0] < source ? -1 : 1;
  return 0;
}

int ByteArray::compare( const char *source ) const
{
  sizetype i;
  for (i = 0; i < arraySize && source[i] != '\0'; i++)
    if (source[i] != ((char*)data)[i])
      return ((char*)data)[i] < source[i] ? -1 : 1;
  return i < arraySize ? 1 : (source[i] == '\0' ? 0 : -1);
}

int ByteArray::compare( const ByteArray &source ) const
{
  sizetype i;
  for (i = 0; i < arraySize && i < source.arraySize; i++)
    if (((char*)source.data)[i] != ((char*)data)[i])
      return ((char*)data)[i] < ((char*)source.data)[i] ? -1 : 1;
  return i < arraySize ? 1 : (i < source.arraySize ? -1 : 0);
}

sizetype ByteArray::find( char source ) const
{
  for (sizetype i = 0; i < arraySize; i++)
    if (((char*)data)[i] == source)
      return i;
  return arraySize;
}

sizetype ByteArray::find( const char *source ) const
{
  return find(ByteArray(source));
}

sizetype ByteArray::find( const ByteArray &source ) const
{
  if (arraySize < source.arraySize)
    return arraySize;
  uinttype64 sourceHash = 0, targetHash = 0;
  uinttype64 hashPower = 1;
  for (sizetype i = 0; i < source.arraySize; i++)
  {
    sourceHash = sourceHash * 239017 + ((char*)(source.data))[i];
    hashPower *= 239017;
    targetHash = targetHash * 239017 + ((char*)data)[i];
  }
  for (sizetype i = 0; i + source.arraySize <= arraySize; i++)
  {
    if (targetHash == sourceHash)
    {
      bool equal = true;
      for (sizetype j = 0; j < source.arraySize; j++)
        if (((char*)data)[i + j] != ((char*)(source.data))[j])
        {
          equal = false;
          break;
        }
      if (equal)
        return i;
    }
    if (i + source.arraySize < arraySize)
      targetHash = targetHash * 239017 + ((char*)data)[i + source.arraySize] - hashPower * ((char*)data)[i];
  }
  return arraySize;
}

ByteArray ByteArray::subString( sizetype index, sizetype size ) const
{
  // TODO: may be use checks?
  return ByteArray((char*)data + index, size);
}

void ByteArray::write( void *target, sizetype size ) const
{
  // TODO: may be use checks?
  if (size > arraySize)
    size = arraySize;
  memoryCopy(target, data, size);
}

char* ByteArray::cString()
{
  return (char*)data;
}

const char* ByteArray::cString() const
{
  return (char*)data;
}

bool ByteArray::operator < ( char source ) const
{
  return compare(source) < 0;
}

bool ByteArray::operator < ( const char *source ) const
{
  return compare(source) < 0;
}

bool ByteArray::operator < ( const ByteArray &source ) const
{
  return compare(source) < 0;
}

bool ByteArray::operator <= ( char source ) const
{
  return compare(source) <= 0;
}

bool ByteArray::operator <= ( const char *source ) const
{
  return compare(source) <= 0;
}

bool ByteArray::operator <= ( const ByteArray &source ) const
{
  return compare(source) <= 0;
}

bool ByteArray::operator > ( char source ) const
{
  return compare(source) > 0;
}

bool ByteArray::operator > ( const char *source ) const
{
  return compare(source) > 0;
}

bool ByteArray::operator > ( const ByteArray &source ) const
{
  return compare(source) > 0;
}

bool ByteArray::operator >= ( char source ) const
{
  return compare(source) >= 0;
}

bool ByteArray::operator >= ( const char *source ) const
{
  return compare(source) >= 0;
}

bool ByteArray::operator >= ( const ByteArray &source ) const
{
  return compare(source) >= 0;
}

bool ByteArray::operator == ( char source ) const
{
  if (arraySize != 1)
    return false;
  return compare(source) == 0;
}

bool ByteArray::operator == ( const char *source ) const
{
  return compare(source) == 0;
}

bool ByteArray::operator == ( const ByteArray &source ) const
{
  if (arraySize != source.arraySize)
    return false;
  return compare(source) == 0;
}

bool ByteArray::operator != ( char source ) const
{
  if (arraySize != 1)
    return true;
  return compare(source) != 0;
}

bool ByteArray::operator != ( const char *source ) const
{
  return compare(source) != 0;
}

bool ByteArray::operator != ( const ByteArray &source ) const
{
  if (arraySize != source.arraySize)
    return true;
  return compare(source) != 0;
}

ByteArray tamias::operator + ( char first, const ByteArray &second )
{
  return ByteArray(first) + ByteArray(second);
}

ByteArray tamias::operator + ( const char *first, const ByteArray &second )
{
  return ByteArray(first) + ByteArray(second);
}

bool tamias::operator < ( char first, const ByteArray &second )
{
  return second.compare(first) > 0;
}

bool tamias::operator < ( const char *first, const ByteArray &second )
{
  return second.compare(first) > 0;
}

bool tamias::operator <= ( char first, const ByteArray &second )
{
  return second.compare(first) >= 0;
}

bool tamias::operator <= ( const char *first, const ByteArray &second )
{
  return second.compare(first) >= 0;
}

bool tamias::operator > ( char first, const ByteArray &second )
{
  return second.compare(first) < 0;
}

bool tamias::operator > ( const char *first, const ByteArray &second )
{
  return second.compare(first) < 0;
}

bool tamias::operator >= ( char first, const ByteArray &second )
{
  return second.compare(first) <= 0;
}

bool tamias::operator >= ( const char *first, const ByteArray &second )
{
  return second.compare(first) <= 0;
}

bool tamias::operator == ( char first, const ByteArray &second )
{
  if (second.size() != 1)
    return false;
  return second.compare(first) == 0;
}

bool tamias::operator == ( const char *first, const ByteArray &second )
{
  return second.compare(first) == 0;
}

bool tamias::operator != ( char first, const ByteArray &second )
{
  if (second.size() != 1)
    return true;
  return second.compare(first) != 0;
}

bool tamias::operator != ( const char *first, const ByteArray &second )
{
  return second.compare(first) != 0;
}

