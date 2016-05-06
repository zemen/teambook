#pragma once

namespace tamias {
  namespace wtf {
    namespace xml {
      class String; // string as a substring of one big
    }
  }
}

#include "../basic/types.h"
#include "../wtf/xml_data.h"

class tamias::wtf::xml::String {
  public:
    String();
    String( Data const &data, sizetype start, sizetype length );
    String( String const &string );
    String& operator = ( String const &string );
    ~String();

    sizetype length() const;
    chartype operator[] ( sizetype index ) const;
    tamias::String value() const;
    String subString( sizetype start, sizetype length ) const;
    bool operator < ( String const &s ) const;

  private:
    Data mData;
    sizetype mStart, mLength;
};

