/*
 * This file [io/buffer.h] is part of the “libtamias” library
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

#ifndef _libtamias_io_buffer_h_
#define _libtamias_io_buffer_h_

#include "../basic/abstract_data.h"
#include "../basic/byte_array.h"
#include "../basic/types.h"
#include "../basic/utilities.h"
#include "../io/iodevice.h"

namespace tamias
{
  class Buffer : public IODevice
  {
    private:
      hidden::AbstractData bufferData;
      sizetype bufferStart, bufferSize;
    public:
      Buffer();
      Buffer( const Buffer &buffer );
      virtual ~Buffer();
      Buffer& operator = ( const Buffer &buffer );
      virtual IODevice* clone() const;

      virtual bool canRead() const;
      virtual bool canWrite() const;
      virtual bool canSeek() const;
      virtual void close();
      virtual bool eof();
      virtual bool waitForRead();
      virtual ByteArray read( sizetype maxSize = (sizetype)-1 );
      virtual sizetype write( const ByteArray &data );
      virtual void seek( sizetype index );

      sizetype size();
      ByteArray preview( sizetype viewSize = (sizetype)-1);
  };
}

#endif /* _libtamias_io_buffer_h_ */

