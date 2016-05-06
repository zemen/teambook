/*
 * This file [io/printer.h] is part of the “libtamias” library
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

#include <cstdarg>
#include "../basic/string.h"
#include "../basic/utilities.h"
#include "../data/pair.h"
#include "../data/queue.h"
#include "../io/iodevice.h"

/*
 * about conversions
 * the generic form is: %<flags><width><precision><modificators><specifier>
 * specifiers:
 *   c — character
 *   d, i — decimal integer
 *   e — float number, exponential format
 *   f — float number, fixed format
 *   g — float number, automatic format
 *   o — octal integer
 *   s — string
 *   x — hex integer
 *   % — special, outputs '%' into output stream
 */

namespace tamias
{
  namespace hidden
  {
    class Conversion;
  }
  class Printer
  {
    public:
      Printer( IODevice const &device );
      Printer( Printer const &printer );
      Printer& operator = ( Printer const &printer );
      virtual ~Printer();

      void close();
      // TODO void flush();

      void print( String const &value );
      void println( String const &value );
      Printer& printf( String const &format );
      Printer& operator << ( String const &value );
      Printer& operator << ( char value );
      Printer& operator << ( char const *value );
      Printer& operator << ( int value );
      Printer& operator << ( unsigned int value );
/*      template <typename Type>
        void println( const Type &value );
      template <typename Type>
        void print( const Type &value );*/
      int _printf( const String &format, ... );
      int vprintf( const String &format, va_list arguments ) __attribute((deprecated));

      static String endln;
      static String intToString( int value, int base = 10 ); // TODO: override for other types
      static String intToString( long long int value, int base = 10 );
      static String intToString( unsigned int value, int base = 10 );
      static String intToString( unsigned long int value, int base = 10 );
    private:
      IODevice *device;
      Queue <hidden::Conversion> buffer;
/*      enum Format
      {
        FORMAT_STRING, FORMAT_CONVERSION
      };*/
//      Queue <Pair <Format, String> > buffer;

      void flushBuffer();
  };

  class hidden::Conversion
  {
    public:
      Conversion( Conversion const &conversion );
      Conversion& operator = ( Conversion const &conversion );
      ~Conversion();
      static Conversion parse( String const &format );
      static Conversion plain( String const &format );

      bool ready() const;
      void add( String const &value ); // and add's for other values
      void add( char value );
      void add( char const *value );
      void add( int value );
      void add( unsigned int value );
      String output() const;
    private:
      enum Type
      {
        TYPE_PLAIN, TYPE_CHARACTER, TYPE_DECIMAL, TYPE_OCTAL, TYPE_HEX, TYPE_FLOAT, TYPE_EXPONENT, TYPE_STRING
      } type;
      int width; // special value is -1
      char widthPadder;
      String result;
      bool mReady;

      Conversion();
  };
}

