/*
 * This file [basic/abstract_data.cpp] is part of the “libtamias” library
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

#include "../../include/basic/abstract_data.h"

using tamias::sizetype;
using tamias::utilities::assert;
using tamias::utilities::memoryCopy;
using tamias::utilities::min;
using tamias::hidden::AbstractData;
using tamias::OutOfMemoryException;
using tamias::OutOfBoundsException;

AbstractData::AbstractData( sizetype initialSize )
{
  assert<OutOfMemoryException>(initialSize <= MAXSIZE);
  data = ::realloc(NULL, initialSize);
  assert<OutOfMemoryException>(data != NULL || initialSize == 0);
  dataSize = initialSize;
}

AbstractData::AbstractData( const AbstractData &source )
{
  data = ::realloc(NULL, source.dataSize);
  assert<OutOfMemoryException>(data != NULL || source.dataSize == 0);
  dataSize = source.dataSize;
  memoryCopy(data, source.data, source.dataSize);
}

AbstractData& AbstractData::operator = ( const AbstractData &source )
{
  data = ::realloc(data, source.dataSize);
  assert<OutOfMemoryException>(data != NULL || source.dataSize == 0);
  dataSize = source.dataSize;
  memoryCopy(data, source.data, source.dataSize);
  return *this;
}

AbstractData::~AbstractData( void )
{
  if (data != NULL)
    ::free(data);
  data = NULL;
  dataSize = 0;
}

void AbstractData::autoReserve( sizetype newSize )
{
  assert<OutOfMemoryException>(newSize <= MAXSIZE);
  sizetype targetSize = dataSize;
  while (targetSize < newSize)
    targetSize = min(targetSize * 2 + (targetSize == 0), MAXSIZE);
  while (targetSize / 4 >= newSize && targetSize > 0)
    targetSize /= 2;
  manualReserve(targetSize);
}

void AbstractData::autoReserveUp( sizetype newSize )
{
  assert<OutOfMemoryException>(newSize <= MAXSIZE);
  sizetype targetSize = dataSize;
  while (targetSize < newSize)
    targetSize = min(targetSize * 2 + (targetSize == 0), MAXSIZE);
  manualReserve(targetSize);
}

void AbstractData::manualReserve( sizetype newSize )
{
  assert<OutOfMemoryException>(newSize <= MAXSIZE);
  if (newSize == dataSize)
    return;
  void *temp = ::realloc(data, newSize);
  assert<OutOfMemoryException>(temp != NULL || newSize == 0);
  data = temp, dataSize = newSize;
}

void* AbstractData::getData() const
{
  return data;
}

