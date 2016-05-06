/*
 * This file [io/printer.cpp] is part of the “libtamias” library
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

#include "../../include/io/printer.h"

using tamias::Printer;
using tamias::hidden::Conversion;

tamias::String Printer::endln = String::fromUtf8("\n");
char digits[] = "0123456789abcdefghijklmnopqrstuv"; // for up to 32-based numbers

Printer::Printer( IODevice const &newDevice ) : device(newDevice.clone()), buffer()
{
}

Printer::Printer( Printer const &printer ) : device(printer.device->clone()), buffer(printer.buffer)
{
}

Printer& Printer::operator = ( Printer const &printer )
{
  device = printer.device->clone();
  buffer = printer.buffer;
  return *this;
}

Printer::~Printer()
{
  delete device;
}

void Printer::close()
{
  device->close();
}

void Printer::print( tamias::String const &value )
{
  buffer.push(Conversion::plain(value));
  flushBuffer();
}

void Printer::println( tamias::String const &value )
{
  buffer.push(Conversion::plain(value + endln));
  flushBuffer();
}

Printer& Printer::printf( String const &format )
{
  static const String specifiers = "aAcdeEfFgGiopsuxX%";
  String temp = "";
  enum { STATE_NORMAL, STATE_CONVERSION } state = STATE_NORMAL; // The canonical way is to use three states. Ask Shalyto from SPbSU IFMO for more funny comments.
  for (sizetype i = 0; i < format.length(); i++)
  {
    if (state == STATE_NORMAL && format[i] == '%')
    {
      if (temp != "")
        buffer.push(Conversion::parse(temp)), temp = "";
      state = STATE_CONVERSION;
    }
    temp += format[i];
    if (state == STATE_CONVERSION && temp.length() != 1 && specifiers.find(format[i]) != specifiers.length())
    {
      buffer.push(Conversion::parse(temp)), temp = "";
      state = STATE_NORMAL;
    }
  }
  if (temp != "")
    buffer.push(Conversion::parse(temp)), temp = "";
  flushBuffer();
  return *this;
}

Printer& Printer::operator << ( const String &value )
{
  if (buffer.size() == 0)
    return *this;
  buffer.front().add(value);
  flushBuffer();
  return *this;
}

Printer& Printer::operator << ( char value )
{
  if (buffer.size() == 0)
    return *this;
  buffer.front().add(value);
  flushBuffer();
  return *this;
}

Printer& Printer::operator << ( char const *value )
{
  if (buffer.size() == 0)
    return *this;
  buffer.front().add(value);
  flushBuffer();
  return *this;
}

Printer& Printer::operator << ( int value )
{
  if (buffer.size() == 0)
    return *this;
  buffer.front().add(value);
  flushBuffer();
  return *this;
}

Printer& Printer::operator << ( unsigned int value )
{
  if (buffer.size() == 0)
    return *this;
  buffer.front().add(value);
  flushBuffer();
  return *this;
}

// TODO: full support of
int Printer::_printf( const String &format, ... )
{
  va_list ap;
  va_start(ap, format);
  int result = vprintf(format, ap);
  va_end(ap);
  return result;
}

int Printer::vprintf( const String &format, va_list ap )
{
  String output = "";
  int result = 0;
  for (sizetype i = 0; i < format.length(); i++)
  {
    if (format[i] != '%')
    {
      output += format[i];
      continue;
    }
    String temp = format[i];
    i++;
    if (i >= format.length() || format[i] == '%')
    {
      output += temp;
      continue;
    }
    bool fillZero = false;
    if (format[i] == '0')
      temp += format[i], i++, fillZero = true;
    if (i >= format.length())
    {
      output += temp;
      continue;
    }
    sizetype fillSize = 0;
    if (format[i] == '*')
      fillSize = va_arg(ap, sizetype), temp += format[i], i++;
    else
    {
      //...
    }
    if (i >= format.length())
    {
      output += temp;
      continue;
    }
//     if (format[i])
    temp += format[i];
    if (format[i] == 'c')
      temp = (chartype)va_arg(ap, chartype);
    else if (format[i] == 'd' || format[i] == 'i')
      temp = intToString(va_arg(ap, int), 10);
    else if (format[i] == 's')
      temp = String((char*)va_arg(ap, char*));
    else if (format[i] == '$')
    {
      if (++i >= format.length())
      {
        output += temp;
        continue;
      }
      temp += format[i];
      if (format[i] == 'S')
      {
        String *ptr = (String*)va_arg(ap, String*);
        temp = String(*ptr);
      }
    }
//     else if (format[i] == 'f')
//     {
//       double value = (double)va_arg(ap, double);
//       temp = Printable::floatToString(va_arg(ap, double));
//     }
    while (temp.length() < fillSize)
      temp = String(fillZero ? '0' : ' ') + temp;
    output += temp;
    // %[['0']('*'|digit+)][.digit+]
    // ('c'|'d'|'f'|'i'|'ld'|'lf'|'li'|'lld'|'llf'|'lli'|'llu'|'llx'|'lu'|'lx'|'Ld'|'Lf'|'Lu'|'Lu'|'Lx'|'Z'|'p'|'s'|'S'|'u'|'x')
  }
  device->write(output.toUtf8());
  return result;
}

void Printer::flushBuffer()
{
  while (true)
  {
    if (buffer.size() == 0)
      return;
    if (!buffer.front().ready())
      return;
    device->write(buffer.pop().output().toUtf8());
  }
}

tamias::String Printer::intToString( int value, int base )
{
  //TODO if (base > 32) Exception();
  String result = "";
  if (value == 0)
    result = "0";
  for (int absValue = utilities::abs(value); absValue > 0; absValue /= base)
    result += digits[absValue % base];
  if (value < 0)
    result += '-';
  utilities::reverse(result.begin(), result.end());
  return result;
}

tamias::String Printer::intToString( long long int value, int base )
{
  //TODO if (base > 32) Exception();
  String result = "";
  if (value == 0)
    result = "0";
  for (long long int absValue = utilities::abs(value); absValue > 0; absValue /= base)
    result += digits[absValue % base];
  if (value < 0)
    result += '-';
  utilities::reverse(result.begin(), result.end());
  return result;
}

tamias::String Printer::intToString( unsigned int value, int base )
{
  //TODO if (base > 32) Exception();
  String result = "";
  if (value == 0)
    result = "0";
  for (; value > 0; value /= base)
    result += digits[value % base];
  utilities::reverse(result.begin(), result.end());
  return result;
}

tamias::String Printer::intToString( unsigned long int value, int base )
{
  //TODO if (base > 32) Exception();
  String result = "";
  if (value == 0)
    result = "0";
  for (; value > 0; value /= base)
    result += digits[value % base];
  utilities::reverse(result.begin(), result.end());
  return result;
}

Conversion::Conversion( Conversion const &conversion ) : type(conversion.type), width(conversion.width), widthPadder(conversion.widthPadder),
                                                         result(conversion.result), mReady(conversion.mReady)
{
}

Conversion& Conversion::operator = ( Conversion const &conversion )
{
  type = conversion.type;
  width = conversion.width;
  widthPadder = conversion.widthPadder;
  result = conversion.result;
  mReady = conversion.mReady;
  return *this;
}

Conversion::~Conversion()
{
}

Conversion Conversion::parse( String const &format )
{ // TODO: допилить
  Conversion conversion;
  if (format.length() == 0)
    return conversion;
  if (format[0] != '%')
  {
    conversion.type = TYPE_PLAIN;
    conversion.result = format;
    conversion.mReady = true;
    return conversion;
  }
  sizetype i = 1;
  if (format[i] == '0')
    conversion.widthPadder = '0', i++;
  while ('0' <= format[i] && format[i] <= '9')
    conversion.width = conversion.width * 10 + format[i] - '0', i++;
  if (format[i] == '*')
    conversion.width = -1, i++;
  switch (format[i])
  {
    case 'c': conversion.type = TYPE_CHARACTER; break;
    case 'd': conversion.type = TYPE_DECIMAL; break;
    case 's': conversion.type = TYPE_STRING; break;
    case '%': conversion.type = TYPE_PLAIN, conversion.result = '%', conversion.mReady = true; break;
  }
  return conversion;
}

Conversion Conversion::plain( String const &format )
{
  Conversion conversion;
  conversion.type = TYPE_PLAIN;
  conversion.result = format;
  conversion.mReady = true;
  return conversion;
}

bool Conversion::ready() const
{
  return mReady;
}

void Conversion::add( String const &value )
{
  if (width == -1)
    return;
  if (type == TYPE_STRING && !mReady)
    result = value, mReady = true;
}

void Conversion::add( char value )
{
  if (width == -1)
    return;
  if (type == TYPE_CHARACTER && !mReady)
    result = value, mReady = true;
}

void Conversion::add( char const *value )
{
  if (width == -1)
    return;
  if (type == TYPE_STRING && !mReady)
    result = value, mReady = true;
}

void Conversion::add( int value )
{
  if (width == -1)
  {
    width = value;
    return;
  }
  if (mReady)
    return;
  mReady = true;
  switch (type)
  {
    case TYPE_DECIMAL: result = Printer::intToString(value, 10); break;
    case TYPE_HEX: result = Printer::intToString(value, 16); break;
    case TYPE_OCTAL: result = Printer::intToString(value, 8); break;
    default: mReady = false;
  }
}

void Conversion::add( unsigned int value )
{
  if (width == -1)
  {
    width = value;
    return;
  }
  if (mReady)
    return;
  mReady = true;
  switch (type)
  {
    case TYPE_DECIMAL: result = Printer::intToString(value, 10); break;
    case TYPE_HEX: result = Printer::intToString(value, 16); break;
    case TYPE_OCTAL: result = Printer::intToString(value, 8); break;
    default: mReady = false;
  }
}

tamias::String Conversion::output() const
{
  String padding = "";
  while (padding.length() + result.length() < (sizetype)width)
    padding += widthPadder;
  return padding + result;
}

Conversion::Conversion() : type(TYPE_PLAIN), width(0), widthPadder(' '), result(""), mReady(false)
{
}

