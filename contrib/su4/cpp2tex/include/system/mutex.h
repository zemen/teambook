/*
 * This file [system/mutex.h] is part of the “libtamias” library
 * Copyright (c) 2007-2010 Oleg Davydov, Yury Petrov
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

namespace tamias {
  class Mutex;
}

#include <time.h>
#include <unistd.h>
#include <linux/futex.h>
#include <sys/syscall.h>
#include "../basic/time.h"

class tamias::Mutex {
  public:
    Mutex( int value = 0 );
    Mutex( Mutex const &mutex );
    Mutex& operator = ( Mutex const &mutex );
    ~Mutex();

      // Waits while mValue == value. Returns 0.
    int wait( int value );
      // Waits while mValue == value, but no more then time. Returns 0 iff exited because of value change, not timeout.
    int wait( int value, Time const &time );
      // Wakes up at most proc waitings threads. proc == 0 means wake all. Returns number of woken threads.
    int wake( int proc = 0 );
      // Sets mValue as value and if wakeUp == true, wakes up waiting threads (see above).
    void set( int value, bool wakeUp = true, int proc = 0);
      // Returns mutexValue.
    int value() const;

  private:
    int mValue;
};

