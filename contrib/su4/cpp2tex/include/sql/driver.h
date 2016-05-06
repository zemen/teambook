/*
 * This file [sql/driver.h] is part of the “libtamias” library
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

#ifndef _libtamias_sql_driver_h_
#define _libtamias_sql_driver_h_

#include <dlfcn.h>
#include "../basic/types.h"
#include "../basic/string.h"
#include "../sql/exception.h"

namespace tamias
{
  namespace sql
  {
    class Driver
    {
      public:
        Driver();
        Driver( const Driver &driver );
        virtual ~Driver();
        Driver& operator = ( const Driver &driver );

        virtual uinttype32 setHost( const String &newHost ) = 0;
        virtual uinttype32 setUser( const String &newUser ) = 0;
        virtual uinttype32 setUser( const String &newUser, const String &newPassword ) = 0;
        virtual uinttype32 setDatabase( const String &newDatabase ) = 0;

        virtual uinttype32 connect() = 0;
        virtual uinttype32 disconnect() = 0;

        virtual uinttype32 query( const String &query, uinttype32 *resultHandle ) = 0;
        virtual uinttype32 resultNext( uinttype32 resultHandle ) = 0;
        virtual uinttype32 resultFree( uinttype32 resultHandle ) = 0;
        virtual uinttype32 resultGet( uinttype32 resultHandle, sizetype column, String *result ) = 0;
        virtual uinttype32 resultGet( uinttype32 resultHandle, const String &column, String *result ) = 0;

        virtual String errorString( uinttype32 error ) = 0;
        virtual void errorFree( uinttype32 error ) = 0;
    };

    class ExternalDriver
    {
      private:
        typedef Driver* (*CreateFunction)();
      public:
        ExternalDriver();
        ExternalDriver( const ExternalDriver &driver );
        ~ExternalDriver();
        ExternalDriver& operator = ( const ExternalDriver &driver );
        static Driver* loadDriver( const String &fileName );
    };
  }
}

#endif /* _libtamias_sql_driver_h_ */
