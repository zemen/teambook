#pragma once

namespace tamias {
  namespace wtf {
    namespace sax {
      class Callback;
    }
  }
}

#include "../basic/string.h"

class tamias::wtf::sax::Callback {
  protected:
    Callback();
    virtual ~Callback();

    virtual void start();
    virtual void finish();
    virtual void elementBegin( String const &name );
    virtual void elementEnd();
    virtual void attribute( String const &name, String const &value );
    virtual void text( String const &text );
    virtual void error( String const &comment ) = 0;

  private:
    Callback( Callback const &callback );
    Callback& operator = ( Callback const &callback );

  friend class Parser;
};

