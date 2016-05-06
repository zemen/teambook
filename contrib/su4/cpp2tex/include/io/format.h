/*
 * This file [io/format.h] is part of the “libtamias” library
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
  class Format;
}

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

#include "../basic/exception.h"
#include "../basic/string.h"
#include "../basic/utilities.h"
#include "../data/pair.h"
#include "../data/vector.h"

class tamias::Format {
  public:
    Format( String const &format );
    Format( Format const &format );
    Format& operator = ( Format const &format );
    virtual ~Format();

    Format& operator << ( int value );
    Format& operator << ( long value );
    Format& operator << ( long long value );
    Format& operator << ( unsigned int value );
    Format& operator << ( unsigned long value );
    Format& operator << ( unsigned long long value );
    Format& operator << ( char value );
    Format& operator << ( char const *value );
    Format& operator << ( String const &value );

    bool ready();
    operator String() const;
    String output() const;

    static String intToString( int value );
    static String intToString( long value );
    static String intToString( long long value );
    static String intToString( unsigned int value );
    static String intToString( unsigned long value );
    static String intToString( unsigned long long value );

  protected:
    enum ValueType {
      TYPE_ECHO, TYPE_CHARACTER, TYPE_DECIMAL, TYPE_OCTAL, TYPE_HEX, TYPE_FLOAT, TYPE_EXPONENT, TYPE_STRING
    };
    virtual String handle( ValueType type, String const &spec, int value );
    virtual String handle( ValueType type, String const &spec, long value );
    virtual String handle( ValueType type, String const &spec, long long value );
    virtual String handle( ValueType type, String const &spec, unsigned int value );
    virtual String handle( ValueType type, String const &spec, unsigned long value );
    virtual String handle( ValueType type, String const &spec, unsigned long long value );
    virtual String handle( ValueType type, String const &spec, char value );
    virtual String handle( ValueType type, String const &spec, char const *value );
    virtual String handle( ValueType type, String const &spec, String const &value );

  private:
    Vector <Pair <ValueType, String> > mData;
    tamias::sizetype mIndex;

    void skip();
};

