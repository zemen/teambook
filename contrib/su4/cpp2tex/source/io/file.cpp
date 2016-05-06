/*
 * This file [io/file.cpp] is part of the “libtamias” library
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

#include "../../include/io/file.h"

using tamias::sizetype;
using tamias::utilities::min;
using tamias::ByteArray;
using tamias::IODevice;
using tamias::IOException;
using tamias::File;

File File::stdin = File(0, OPEN_READ);
File File::stdout = File(1, OPEN_WRITE);
File File::stderr = File(2, OPEN_WRITE);

File::File( int newHandle, OpenMode newOpenMode ) : IODevice(), handle(newHandle),
                                                    filePos(-1), fileSize(-1), openMode(newOpenMode)
{
  if (openMode == OPEN_READ || openMode == OPEN_RW)
  {
    fileSize = ::lseek(handle, 0, SEEK_END);
    filePos = ::lseek(handle, 0, SEEK_SET);
  }
}

File::File() : IODevice(), handle(-1), filePos(-1), fileSize(-1), openMode(CLOSED)
{
}

File::File( const File &file ) : IODevice(file), handle(file.handle),
                                 filePos(file.filePos), fileSize(file.fileSize), openMode(file.openMode)
{
}

File::~File()
{
  handle = -1, openMode = CLOSED;
}

File& File::operator = ( const File &file )
{
  IODevice::operator = (file);
  handle = file.handle;
  filePos = file.filePos;
  fileSize = file.fileSize;
  openMode = file.openMode;
  return *this;
}

IODevice* File::clone() const
{
  return new File(*this);
}

// TODO: errno -> ::errno???

File File::openRead( const ByteArray &fileName )
{
  int fileHandle = ::open(fileName.cString(), O_RDONLY);
  if (fileHandle == -1)
    throw IOException::fromErrno(errno);
  return File(fileHandle, OPEN_READ);
}

File File::openWrite( const ByteArray &fileName )
{
  int fileHandle = ::creat(fileName.cString(), 0644);
  if (fileHandle == -1)
    throw IOException::fromErrno(errno);
  return File(fileHandle, OPEN_WRITE);
}

bool File::canRead() const
{
  return openMode == OPEN_READ || openMode == OPEN_RW;
}

bool File::canWrite() const
{
  return openMode == OPEN_WRITE || openMode == OPEN_RW;
}

bool File::canSeek() const
{
  return openMode == OPEN_READ || openMode == OPEN_RW;
}

void File::close()
{
  if (openMode != OPEN_READ && openMode != OPEN_WRITE && openMode != OPEN_RW)
  // TODO: define string constants somewhere
    throw IOException(IOException::ERROR_IO_INVALID_OPERATION, "try to close unopened file");
  if (::close(handle) != 0)
    throw IOException::fromErrno(errno);
  openMode = CLOSED;
}

bool File::eof()
{
  if (openMode != OPEN_READ && openMode != OPEN_RW)
    throw IOException(IOException::ERROR_IO_INVALID_OPERATION, "try to test eof in non-readable file");
  // TODO: There are files (for example, in /proc), their size is 0, but they aren't empty
  return filePos >= fileSize;
}

bool File::waitForRead()
{
  throw IOException(IOException::ERROR_IO_INVALID_OPERATION, "try to wait for data while reading from file");
}

ByteArray File::read( sizetype maxSize )
{
  ByteArray result;
  if (openMode != OPEN_READ && openMode != OPEN_RW)
    throw IOException(IOException::ERROR_IO_INVALID_OPERATION, "try to read from non-readable file");
  if (maxSize == 0)
    return result;
  while (result.size() < maxSize)
  {
    sizetype currentSize = min(maxSize - result.size(), 1024lu);
    char *data = (char*)::malloc(currentSize);
    sizetype resultSize = ::read(handle, data, currentSize);
    result += ByteArray(data, resultSize);
    filePos += resultSize;
    ::free(data);
    if (resultSize < currentSize)
      break;
  }
  return result;
}

sizetype File::write( const ByteArray &data )
{
  if (openMode != OPEN_WRITE && openMode != OPEN_RW)
    throw IOException(IOException::ERROR_IO_INVALID_OPERATION, "try to write to non-writable file");
  sizetype resultSize = ::write(handle, data.cString(), data.size()); // TODO: well-well...
  return resultSize;
}

void File::seek( sizetype index )
{
  if (openMode != OPEN_READ && openMode != OPEN_RW)
    throw IOException(IOException::ERROR_IO_INVALID_OPERATION, "try to seek in non-seekable file");
  ::lseek(handle, index, SEEK_SET);
}

