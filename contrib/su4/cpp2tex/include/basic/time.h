/*
 * This file [basic/time.h] is part of the “libtamias” library
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

#ifndef _libtamias_basic_time_h_
#define _libtamias_basic_time_h_

#include "../basic/types.h"

namespace tamias
{
/*
        second  (second) = 1 second
   millisecons (msecond) = 1e-3 seconds
   microsecond (usecond) = 1e-6 seconds
    nanosecond (nsecond) = 1e-9 seconds
 */
  class Time
  {
    private:
      inttype64 timeSeconds;
      uinttype32 timeNanoSeconds;
    public:
      Time( inttype64 seconds = 0, uinttype32 nanoSeconds = 0 );
      Time( const Time &time );
      ~Time();
      Time& operator = ( const Time &time );
      static Time fromSeconds( long double seconds );

      inttype64& seconds();
      inttype64 seconds() const;
      void setSeconds( inttype64 seconds );
      uinttype32& nanoSeconds();
      uinttype32 nanoSeconds() const;
      void setNanoSeconds( uinttype32 nanoSeconds );

      long double toSeconds() const;
      Time& operator += ( const Time &time );
      Time& operator -= ( const Time &time );
      Time operator + ( const Time &time ) const;
      Time operator - ( const Time &time ) const;

      int compare( const Time &time ) const;
      bool operator == ( const Time &time ) const;
      bool operator != ( const Time &time ) const;
      bool operator < ( const Time &time ) const;
      bool operator <= ( const Time &time ) const;
      bool operator > ( const Time &time ) const;
      bool operator >= ( const Time &time ) const;
  };
}

#endif /* _libtamias_basic_time_h_ */

