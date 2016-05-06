/*
 * This file [basic/mutex.cpp] is part of the “libtamias” library
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

#include "../../include/basic/mutex.h"

using tamias::Mutex;

Mutex::Mutex( int value ) : mutexValue(value)
{
}

Mutex::Mutex( const Mutex &mutex ) : mutexValue(mutex.mutexValue)
{
}

Mutex::~Mutex()
{
}

Mutex& Mutex::operator = ( const Mutex &mutex )
{
  mutexValue = mutex.mutexValue;
  return *this;
}

int Mutex::wait( int value )
{
  return ::syscall(__NR_futex, &mutexValue, FUTEX_WAIT, value, NULL, NULL, 0);
}

int Mutex::wait( int value, const Time &time )
{
  struct timespec futexTimeout;
  futexTimeout.tv_sec = time.seconds();
  futexTimeout.tv_nsec = time.nanoSeconds();
  return ::syscall(__NR_futex, &mutexValue, FUTEX_WAIT, value, &futexTimeout, NULL, 0);
}

int Mutex::wake( int proc )
{
  return ::syscall(__NR_futex, &mutexValue, FUTEX_WAKE, proc, NULL, NULL, 0);
}

void Mutex::set( int value, bool wakeUp, int proc )
{
  mutexValue = value;
  wakeUp && wake(proc); // call wake if wakeUp flag is true.
}

int Mutex::get() const
{
  return mutexValue;
}

