#pragma once

namespace tamias {
  namespace wtf {
    namespace xml {
      class Data; // provides common access to base string
    }
  }
}

#include "../basic/string.h"
#include "../basic/types.h"
#include "../data/flyweight.h"

class tamias::wtf::xml::Data : private Flyweight <String> {
  public:
    Data( tamias::String const &s = "" );
    Data( Data const &data );
    Data& operator = ( Data const &data );
    ~Data();

    sizetype length() const;
    chartype operator[] ( sizetype index ) const;
    tamias::String subString( sizetype start, sizetype length ) const;
    Data& append( tamias::String const &s );
};

