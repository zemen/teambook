/*
 * libtamias/wtf/utilities.h — some useful functions
 */

#pragma once

#include "../basic/byte_array.h"
#include "../basic/string.h"
#include "../basic/types.h"
#include "../main/vector.h"

namespace tamias
{
  namespace wtf
  {
    namespace utilities
    {
      Vector <String> splitString( const String &source, chartype splitter );
      Vector <String> splitString( const String &source, const String &splitter );
      String randomString( sizetype length ) __attribute((deprecated)); // use Random.nextToken() instead. LCGRandom is now awailible
      ByteArray md5Sum( const ByteArray &source );
      inttype64 stringToInt( const String &source );
      bool isValidInt( String const &source );
      String intToString( inttype64 value, sizetype zeros = 0 ) __attribute((deprecated)); // use tamias::Printer::intToString() instead
      bool isAlphaNum( const String &source );
      bool testString( const String &source, const String &pattern );
    }
  }
}

