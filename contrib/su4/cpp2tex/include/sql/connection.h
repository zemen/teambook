/*
 * This file [sql/connection.h] is part of the “libtamias” library
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

#ifndef _libtamias_sql_connection_h_
#define _libtamias_sql_connection_h_

#include "../sql/driver.h"
#include "../sql/result.h"
#include "../basic/string.h"

namespace tamias
{
  namespace sql
  {
    class Connection
    {
      private:
        Driver* driver;
        uinttype32 error;
      public:
        Connection( Driver *newDriver );
        Connection( const Connection &connection );
        ~Connection();
        Connection& operator = ( const Connection &connection );
        void connect( const String &host, const String &user, const String &password, const String &database );
        void close();
        Result query( const String &str );
    };
  }
}

#endif /* _libtamias_sql_connection_h_ */
