/*
 * This file [basic/time.cpp] is part of the “libtamias” library
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

#include "../../include/basic/time.h"

using tamias::inttype32;
using tamias::inttype64;
using tamias::uinttype32;
using tamias::Time;

Time::Time( inttype64 seconds, uinttype32 nanoSeconds ) : timeSeconds(seconds), timeNanoSeconds(nanoSeconds)
{
  if (timeNanoSeconds >= (inttype32)1e9)
  {
    timeSeconds += timeNanoSeconds / (inttype32)1e9;
    timeNanoSeconds %= (inttype32)1e9;
  }
}

Time::Time( const Time &time ) : timeSeconds(time.timeSeconds), timeNanoSeconds(time.timeNanoSeconds)
{
}

Time::~Time()
{
}

Time& Time::operator = ( const Time &time )
{
  timeSeconds = time.timeSeconds;
  timeNanoSeconds = time.timeNanoSeconds;
  return *this;
}

Time Time::fromSeconds( long double seconds )
{
  inttype64 roundSeconds = (inttype64)seconds;
  return Time(roundSeconds, (inttype32)(1e9 * (seconds - roundSeconds)));
}

inttype64& Time::seconds()
{
  return timeSeconds;
}

inttype64 Time::seconds() const
{
  return timeSeconds;
}

void Time::setSeconds( inttype64 seconds )
{
  timeSeconds = seconds;
}

uinttype32& Time::nanoSeconds()
{
  return timeNanoSeconds;
}

uinttype32 Time::nanoSeconds() const
{
  return timeNanoSeconds;
}

void Time::setNanoSeconds( uinttype32 nanoSeconds )
{
  timeNanoSeconds = nanoSeconds;
}

long double Time::toSeconds() const
{
  return timeSeconds + timeNanoSeconds * 1e-9;
}

Time& Time::operator += ( const Time &time )
{
  timeSeconds += time.timeSeconds;
  timeNanoSeconds += time.timeNanoSeconds;
  // TODO: move this code into separate private method.
  if (timeNanoSeconds >= (inttype32)1e9)
  {
    timeSeconds += timeNanoSeconds / (inttype32)1e9;
    timeNanoSeconds %= (inttype32)1e9;
  }
  return *this;
}

Time& Time::operator -= ( const Time &time )
{
  timeSeconds += -time.timeSeconds - 1;
  timeNanoSeconds += (inttype32)1e9 - time.timeNanoSeconds;
  // TODO: move this code into separate private method.
  if (timeNanoSeconds >= (inttype32)1e9)
  {
    timeSeconds += timeNanoSeconds / (inttype32)1e9;
    timeNanoSeconds %= (inttype32)1e9;
  }
  return *this;
}

Time Time::operator - ( const Time &time ) const
{
  return Time(timeSeconds - time.timeSeconds - 1, timeNanoSeconds - time.timeNanoSeconds + (inttype32)1e9);
}

Time Time::operator + ( const Time &time ) const
{
  return Time(timeSeconds + time.timeSeconds, timeNanoSeconds + time.timeNanoSeconds);
}

int Time::compare( const Time &time ) const
{
  if (timeSeconds != time.timeSeconds)
    return timeSeconds > time.timeSeconds ? 1 : -1;
  if (timeNanoSeconds != time.timeNanoSeconds)
    return timeNanoSeconds > time.timeNanoSeconds ? 1 : -1;
  return 0;
}

bool Time::operator == ( const Time &time ) const
{
  return compare(time) == 0;
}

bool Time::operator != ( const Time &time ) const
{
  return compare(time) != 0;
}

bool Time::operator < ( const Time &time ) const
{
  return compare(time) < 0;
}

bool Time::operator <= ( const Time &time ) const
{
  return compare(time) <= 0;
}

bool Time::operator > ( const Time &time ) const
{
  return compare(time) > 0;
}

bool Time::operator >= ( const Time &time ) const
{
  return compare(time) >= 0;
}

