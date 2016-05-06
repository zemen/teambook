#pragma once

namespace tamias {
  namespace wtf {
    namespace xml {
      class Element;
    }
  }
}

#include "../data/map.h"
#include "../data/tree_rbst.h"
#include "../data/vector.h"
#include "../wtf/xml_string.h"

class tamias::wtf::xml::Element {
  public:
    Element();
    Element( Element const &element );
    Element& operator = ( Element const &element );
    ~Element();

    Element& setName( String const &name );
    Element& setContent( String const &content );
    Element& addAttribute( String const &name, String const &value );
    Element& addElement( Element const &element );

  private:
    String mName, mContent; 
    Vector <String> mAttributes;
    Map <RBSTree, String, String> mValues;
    Vector <Element> mElements;
};

