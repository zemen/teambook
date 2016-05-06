/*
 * This file [basic/mutex.h] is part of the “libtamias” library
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

#ifndef _libtamias_basic_mutex_h_
#define _libtamias_basic_mutex_h_

#include <time.h>
#include <unistd.h>
#include <linux/futex.h>
#include <sys/syscall.h>
#include "../basic/time.h"

namespace tamias
{
  class Mutex
  {
    private:
      int mutexValue;
    public:
      Mutex( int value = 0 );
      Mutex( const Mutex &mutex );
      ~Mutex();
      Mutex& operator = ( const Mutex &mutex );

        // Waits while mutexValue == value. Returns 0.
      int wait( int value );
        // Waits while mutexValue == value, but no more then time. Returns 0 iff exited because of value change, not timeout.
      int wait( int value, const Time &time );
        // Wakes up at most proc waitings threads. proc == 0 means wake all. Returns number of woken threads.
      int wake( int proc = 0 );
        // Sets mutexValue as value and if wakeUp == true, wakes up waiting threads (see above).
      void set( int value, bool wakeUp = true, int proc = 0);
        // Returns mutexValue.
      int get() const;
  };
}

#endif /* _libtamias_basic_mutex_h_ */

