#pragma once

namespace tamias {
  namespace wtf {
    namespace sax {
      class Parser;
    }
  }
}

#include "../data/vector.h"
#include "../wtf/sax_callback.h"

class tamias::wtf::sax::Parser {
  public:
    explicit Parser( Callback &callback );
    ~Parser();

    void parse( String const &document ); // A whole document in one time. Sorry.

  private:
    Parser( Parser const &parser );
    Parser& operator = ( Parser const &parser );

    bool isAlpha( chartype ch );
    bool isSpace( chartype ch );

    void flush();
    bool tag( bool close, bool selfClose );

    Callback &mCallback;

    String temp;
    String tagName;
    bool closeTag, started;
    Vector <String> tagStack, attributeNames, attributeValues;
};

