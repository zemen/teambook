#pragma once

#include <cstdlib>
#include "../basic/byte_array.h"
#include "../basic/exception.h"
#include "../basic/string.h"
#include "../basic/types.h"
#include "../data/pair.h"
#include "../main/vector.h"

namespace tamias
{
  namespace wtf
  {
    namespace web
    {
      class Captcha
      {
        public:
          Captcha( const ByteArray &binaryName, const ByteArray &path );
          Captcha( const Captcha &captcha );
          Captcha& operator = ( const Captcha &captcha );
          ~Captcha();
    
          String generate( const String &key );
          const String& key() const;
          const String& value() const;
        private:
          ByteArray mBinaryName;
          ByteArray mPath;
          String mKey;
          String mValue;
      };
    }
  }
}

