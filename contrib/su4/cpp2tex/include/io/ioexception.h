/*
 * This file [io/ioexception.h] is part of the “libtamias” library
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

#pragma once

#include <cstring> // for strerror
#include "../basic/exception.h"
#include "../basic/string.h"

namespace tamias
{
  class IOException : public Exception
  {
    public:
      enum IOExceptionType
      {
        ERROR_IO_UNKNOWN,
        ERROR_IO_ERRNO,
        ERROR_IO_UNEXPECTED_END_OF_FILE,
        ERROR_IO_INVALID_OPERATION
      };
    private:
      IOExceptionType errorType;
      String errorMessage;
    public:
      IOException( const IOExceptionType newType = ERROR_IO_UNKNOWN, const String &message = "" );
      IOException( const IOException &exception );
      virtual ~IOException();
      IOException& operator = ( const IOException &exception );
      static IOException fromErrno( int stdErrno );

      virtual const char* type() const;
      virtual const String& report() const;
      IOExceptionType getType() const;
  };
}

