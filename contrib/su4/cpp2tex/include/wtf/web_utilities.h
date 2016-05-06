#pragma once

#include "../basic/byte_array.h"
#include "../basic/string.h"
#include "../basic/types.h"

namespace tamias
{
  namespace wtf
  {
    namespace web
    {
      namespace utilities
      {
        String decodeURIString( const ByteArray &source );
        String encodeHTTPParameter( const String &source );
      }
    }
  }
}

