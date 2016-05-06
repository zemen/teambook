/*
 * This file [basic/date.cpp] is part of the “libtamias” library
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

#include "../../include/basic/date.h"

using tamias::inttype64;
using tamias::sizetype;
using tamias::uinttype64;
using tamias::Date;
using tamias::String;
using tamias::Time;

Date::Date( const Time &time ) : Time(time)
{
}

Date::Date() : Time()
{
}

Date::Date( const Date &date ) : Time(date)
{
}

Date& Date::operator = ( const Date &date )
{
  Time::operator = (date);
  return *this;
}

Date::~Date()
{
}

Date Date::fromTimestamp( inttype64 timestamp )
{
  return Date(Time(timestamp, 0));
}

Date Date::now()
{
  struct timespec tp;
  ::clock_gettime(CLOCK_REALTIME, &tp);
  return Date(Time(tp.tv_sec, tp.tv_nsec));
}

Time Date::operator - ( const Date &date ) const
{
  return Time::operator - (date);
}

Date Date::operator + ( const Time &time ) const
{
  return Date(*(Time*)this + time);
}

Date Date::operator - ( const Time &time ) const
{
  return Date(*(Time*)this - time);
}

bool Date::isLeapYear( inttype64 year )
{
  return (year + 1970) % 4 == 0 && ((year + 1970) % 100 != 0 || (year + 1970) % 400 == 0);
}

// TODO: move this function somewhere
String intToString( inttype64 value, sizetype zeros )
{
  String result = "";
  if (value < 0)
    result += '-', value = -value;
  inttype64 divide = 1;
  while (value / 10 > divide || zeros > 1)
    divide *= 10, zeros--;
  while (divide > 0)
    result += '0' + value / divide % 10, divide /= 10;
  return result;
}

String Date::format( const String &pattern ) const
{
  static int monthLength[12] = {31, -1, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  static char weekdayName[7][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  static char monthName[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  String result = "";
  inttype64 day = seconds() / (24 * 3600), year = 0, month = 0;
  inttype64 rest = seconds() - day * 24 * 3600;
  while (day >= 365 + isLeapYear(year))
    day -= 365 + isLeapYear(year++);
  inttype64 dayInYear = day;
  inttype64 dayOfWeek = (day + 4) % 7;
  monthLength[1] = 28 + isLeapYear(year);
  while (day >= monthLength[month])
    day -= monthLength[month++];
  inttype64 hour = rest / 3600, minute = (rest / 60) % 60, second = rest % 60;
  for (sizetype i = 0; i < pattern.length(); i++)
    if (pattern[i] == 'H')
      result += intToString(hour, 2);
    else if (pattern[i] == 'Y')
      result += intToString(year + 1970, 4);
    else if (pattern[i] == 'd')
      result += intToString(day + 1, 2);
    else if (pattern[i] == 'i')
      result += intToString(minute, 2);
    else if (pattern[i] == 'm')
      result += intToString(month, 2);
    else if (pattern[i] == 'r')
      result += String(weekdayName[dayOfWeek]) + ", " +
                intToString(day + 1, 2) + " " + monthName[month] + " " + intToString(year + 1970, 4) + " " +
                intToString(hour, 2) + ":" + intToString(minute, 2) + ":" + intToString(second, 2) + " +0000";
    else if (pattern[i] == 's')
      result += intToString(second, 2);
    else if (pattern[i] == 'z')
      result += intToString(dayInYear, 3);
    else if (pattern[i] == 'u')
      result += intToString(nanoSeconds(), 9);
    else
      result += pattern[i];
  return result;
}

