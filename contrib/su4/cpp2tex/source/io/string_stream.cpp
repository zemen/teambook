/*
 * This file [io/string_stream.cpp] is part of the “libtamias” library
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

#include "../../include/io/string_stream.h"

using tamias::sizetype;
using tamias::ByteArray;
using tamias::IODevice;
using tamias::StringStream;
using tamias::StringStreamClone;

StringStream::StringStream() : streamBuffer()
{
}

StringStream::StringStream( const StringStream &stream ) : streamBuffer(stream.streamBuffer)
{
}

StringStream& StringStream::operator = ( const StringStream &stream )
{
  streamBuffer = stream.streamBuffer;
  return *this;
}

StringStream::~StringStream()
{
}

IODevice* StringStream::clone() const
{
  return new StringStreamClone(&streamBuffer);
}

bool StringStream::canRead() const
{
  return false;
}

bool StringStream::canWrite() const
{
  return true;
}

bool StringStream::canSeek() const
{
  return false;
}

void StringStream::close()
{
}

bool StringStream::eof()
{
  throw IOException(IOException::ERROR_IO_INVALID_OPERATION, "cannot test eof in StringStream");
}

bool StringStream::waitForRead()
{
  throw IOException(IOException::ERROR_IO_INVALID_OPERATION, "cannot wait in StringStream");
}

ByteArray StringStream::read( sizetype maxSize )
{
  throw IOException(IOException::ERROR_IO_INVALID_OPERATION, "cannot read from StringStream");
}

sizetype StringStream::write( const ByteArray &data )
{
  streamBuffer += data;
  return data.size();
}

void StringStream::seek( sizetype index )
{
  throw IOException(IOException::ERROR_IO_INVALID_OPERATION, "cannot seek in StringStream");
}

const ByteArray& StringStream::output() const
{
  return streamBuffer;
}


// == StringStreamClone ==

StringStreamClone::StringStreamClone( const ByteArray *buffer ) : streamBuffer((ByteArray*)buffer)
// TODO: Что-то здесь не так...
{
}

StringStreamClone::StringStreamClone( const StringStreamClone &stream ) : streamBuffer(stream.streamBuffer)
{
}

StringStreamClone& StringStreamClone::operator = ( const StringStreamClone &stream )
{
  streamBuffer = stream.streamBuffer;
  return *this;
}

StringStreamClone::~StringStreamClone()
{
  streamBuffer = NULL;
}

IODevice* StringStreamClone::clone() const
{
  return new StringStreamClone(*this);
}

bool StringStreamClone::canRead() const
{
  return false;
}

bool StringStreamClone::canWrite() const
{
  return true;
}

bool StringStreamClone::canSeek() const
{
  return false;
}

void StringStreamClone::close()
{
}

bool StringStreamClone::eof()
{
  throw IOException(IOException::ERROR_IO_INVALID_OPERATION, "cannot test eof in StringStream");
}

bool StringStreamClone::waitForRead()
{
  throw IOException(IOException::ERROR_IO_INVALID_OPERATION, "cannot wait in StringStream");
}

ByteArray StringStreamClone::read( sizetype maxSize )
{
  throw IOException(IOException::ERROR_IO_INVALID_OPERATION, "cannot read from StringStream");
}

sizetype StringStreamClone::write( const ByteArray &data )
{
  (*streamBuffer) += data;
  return data.size();
}

void StringStreamClone::seek( sizetype index )
{
  throw IOException(IOException::ERROR_IO_INVALID_OPERATION, "cannot seek in StringStream");
}

const ByteArray& StringStreamClone::output() const
{
  return *streamBuffer;
}

