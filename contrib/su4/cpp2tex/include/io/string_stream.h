/*
 * This file [io/string_stream.h] is part of the “libtamias” library
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

#ifndef _libtamias_io_string_stream_h_
#define _libtamias_io_string_stream_h_

#include "../basic/byte_array.h"
#include "../basic/types.h"
#include "../io/iodevice.h"
#include "../io/ioexception.h"

namespace tamias
{
  class StringStream : public IODevice
  {
    // by now, we support only output string stream
    private:
      ByteArray streamBuffer;
    public:
      StringStream();
      StringStream( const StringStream &stream );
      StringStream& operator = ( const StringStream &stream );
      virtual ~StringStream();
      virtual IODevice* clone() const;

      bool canRead() const;
      bool canWrite() const;
      bool canSeek() const;
      void close();
      bool eof();
      bool waitForRead();
      ByteArray read( sizetype maxSize = (sizetype)-1 );
      sizetype write( const ByteArray &data );
      void seek( sizetype index = 0 );

      const ByteArray& output() const;
  };

  class StringStreamClone : public IODevice
  {
    private:
      ByteArray *streamBuffer;
    public:
      StringStreamClone( const ByteArray *buffer );
      StringStreamClone( const StringStreamClone &stream );
      StringStreamClone& operator = ( const StringStreamClone &stream );
      virtual ~StringStreamClone();
      virtual IODevice* clone() const;

      bool canRead() const;
      bool canWrite() const;
      bool canSeek() const;
      void close();
      bool eof();
      bool waitForRead();
      ByteArray read( sizetype maxSize = (sizetype)-1 );
      sizetype write( const ByteArray &data );
      void seek( sizetype index = 0 );

      const ByteArray& output() const;
  };
}

#endif // _libtamias_io_string_stream_h_

