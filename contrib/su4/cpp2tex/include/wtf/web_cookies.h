#pragma once

#include "../basic/date.h"
#include "../basic/string.h"
#include "../basic/time.h"
#include "../basic/types.h"
#include "../basic/utilities.h"
#include "../io/printer.h"
#include "../wtf/web_utilities.h"

namespace tamias
{
  namespace wtf
  {
    namespace web
    {
      /* see rfc2109 for information about cookies */
      class Cookie
      {
        public:
          Cookie();
    /* I wonder what should do next constructor */
    //       Cookie( const tamias::String cookie );
          Cookie( const String name, const String value );
          Cookie( const Cookie &cookie );
          Cookie& operator = ( const Cookie &cookie );
          ~Cookie();
    
          String name() const;
          String value() const;
          void setExpires( const Date &expires );
          void setMaxAge( const Time &maxAge );
          String output() const;
        private:
          String mName, mValue;
          enum TimeoutType
          {
            TIMEOUT_NONE, TIMEOUT_EXPIRES, TIMEOUT_MAXAGE
          } mTimeoutType;
          Date mTimeoutExpires;
          Time mTimeoutMaxAge;
      };
    }
  }
}

