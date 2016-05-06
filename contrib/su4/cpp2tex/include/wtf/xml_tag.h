#pragma once

namespace tamias {
  namespace wtf {
    namespace xml {
      class Tag;
    }
  }
}

#include "../wtf/xml_string.h"

class tamias::wtf::xml::Tag {
  public:
    enum Type {
      TYPE_NOTAG, TYPE_OPEN, TYPE_CLOSE, TYPE_EMPTY, TYPE_COMMENT, TYPE_SPECIAL
    };
    Tag( Type type, String const& name, String const& content );
    Tag( Tag const &tag );
    Tag& operator = ( Tag const &tag );
    ~Tag();

    Type type() const;
    String const& name() const;
    String const& content() const;

  private:
    Type mType;
    String mName, mContent;
};

