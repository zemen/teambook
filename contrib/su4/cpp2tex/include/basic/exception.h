/*
 * This file [basic/exception.h] is part of the “libtamias” library
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

#include "../basic/generic_exception.h"
#include "../basic/string.h"

namespace tamias
{
  /*  */
  class Exception : public GenericException
  {
    public:
      Exception();
      Exception( const Exception &exception );
      Exception& operator = ( const Exception &exception  );
      virtual ~Exception();

      const char* message() const;
      virtual const char* type() const = 0;
      virtual const String& report() const = 0;
  };

  class CommonException : public Exception
  {
    public:
      CommonException( const String &report );
      CommonException( const CommonException &exception );
      CommonException& operator = ( const CommonException &exception  );
      virtual ~CommonException();

      virtual const char* type() const;
      virtual const String& report() const;
    private:
      String mReport;
  };
};

