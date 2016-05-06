#pragma once

#include "../basic/string.h"
#include "../basic/types.h"

namespace tamias
{
  namespace wtf
  {
    class LCGRandom
    {
      public:
        LCGRandom( uinttype64 seed = 0 );
        ~LCGRandom();

        void setSeed( uinttype64 seed );
        uinttype32 next();
        String nextToken( sizetype length ); // TODO: setup character set
      private:
        LCGRandom( LCGRandom const &random );
        LCGRandom& operator = ( LCGRandom const &random );
        uinttype64 lcg;
    };
  }
}

