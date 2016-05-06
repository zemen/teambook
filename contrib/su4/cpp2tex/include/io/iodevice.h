/*
 * This file [io/iodevice.h] is part of the “libtamias” library
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

#ifndef _libtamias_io_iodevice_h_
#define _libtamias_io_iodevice_h_

#include "../basic/byte_array.h"
#include "../basic/types.h"

namespace tamias
{
  /* abstract class for something that can input and/or output - fs files, sockets, pipes... */
  class IODevice
  {
    public:
      IODevice();
      IODevice( const IODevice &device );
      virtual ~IODevice();
      IODevice& operator = ( const IODevice &device );
      virtual IODevice* clone() const = 0;

      virtual bool canRead() const = 0;
      virtual bool canWrite() const = 0;
      virtual bool canSeek() const = 0;
      virtual void close() = 0;
      virtual bool eof() = 0;
      virtual bool waitForRead() = 0;
      virtual ByteArray read( sizetype maxSize = (sizetype)-1 ) = 0;
      virtual sizetype write( const ByteArray &data ) = 0;
      virtual void seek( sizetype index ) = 0;
//       void writeAll( const ByteData &data );
  };
}

#endif /* _libtamias_io_iodevice_h_ */

