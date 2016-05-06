/*
 * This file [basic/date.h] is part of the “libtamias” library
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

#include <time.h>
#include "../basic/time.h"
#include "../basic/types.h"
#include "../basic/string.h"

namespace tamias
{
  // TODO: leap seconds support, timezone support, etc
  class Date : public Time
  {
    public:
      Date();
      Date( const Date &date );
      Date& operator = ( const Date &date );
      ~Date();

      static Date fromTimestamp( inttype64 timestamp );
      static Date now();
      static bool isLeapYear( inttype64 year ); // remember: year is calculated from 1970

      Time operator - ( const Date &date ) const;
      Date operator + ( const Time &time ) const; // TODO: operator +=, -, -= with Time
      Date operator - ( const Time &time ) const;
      // TODO: format shoud accept all variants that accepts php's data() function — see http://www.php.net/date
      String format( const String &pattern ) const;
    private:
      Date( const Time &time );
  };
}

