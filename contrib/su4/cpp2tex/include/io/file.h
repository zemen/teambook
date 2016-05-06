/*
 * This file [io/file.h] is part of the “libtamias” library
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

#ifndef _libtamias_io_file_h_
#define _libtamias_io_file_h_

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../basic/byte_array.h"
#include "../basic/types.h"
#include "../io/ioexception.h"
#include "../io/iodevice.h"

namespace tamias
{
  class File : public IODevice
  {
    public:
      enum OpenMode
      {
        CLOSED,
        OPEN_READ,
        OPEN_WRITE,
        OPEN_RW
      };
    private:
      int handle;
      uinttype64 filePos, fileSize;
      OpenMode openMode;
      File( int handle, OpenMode newOpenMode );
    public:
      static File stdin;
      static File stdout;
      static File stderr;

      File();
      File( const File &file );
      File& operator = ( const File &file );
      virtual ~File();
      virtual IODevice* clone() const;

      static File openRead( const ByteArray &fileName );
      static File openWrite( const ByteArray &fileName );
      virtual bool canRead() const;
      virtual bool canWrite() const;
      virtual bool canSeek() const;
      virtual void close();
      virtual bool eof();
      virtual bool waitForRead();
      virtual ByteArray read( sizetype maxSize = (sizetype)-1 );
      virtual sizetype write( const ByteArray &data );
      virtual void seek( sizetype index );
  };
}

#endif /* _libtamias_io_file_h_ */

