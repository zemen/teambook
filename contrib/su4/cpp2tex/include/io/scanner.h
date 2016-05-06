/*
 * This file [io/scanner.h] is part of the “libtamias” library
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

#ifndef _libtamias_io_scanner_h_
#define _libtamias_io_scanner_h_

#include "../basic/byte_array.h"
#include "../io/iodevice.h"

namespace tamias
{
  class Scanner
  {
    private:
      IODevice *device;
      bool bufferUsed;
      int buffer;
      void readBuffer();
    public:
      Scanner( const IODevice &device );
      Scanner( const Scanner &scanner );
      Scanner& operator = ( const Scanner &scanner );
      ~Scanner();

      void close();
      bool eof();

      int scanByte();
      int nextByte();
      void skipSpace();
      ByteArray nextToken();
      ByteArray nextLine();
  };
}

#endif /* _libtamias_io_scanner_h_ */

