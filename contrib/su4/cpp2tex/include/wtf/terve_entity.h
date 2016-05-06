#pragma once

#include "../basic/types.h"

namespace tamias
{
  namespace wtf
  {
    namespace terve
    {
      class Entity
      {
        public:
          enum Type
          {
            ENTITY_EMPTY, ENTITY_TEXT, ENTITY_I18N, ENTITY_LINE, ENTITY_GROUP
          };
          Entity( Type type = ENTITY_EMPTY, sizetype value = (sizetype)-1 );
          Entity( const Entity &entity );
          Entity& operator = ( const Entity &entity );
          ~Entity();
    
          Type type() const;
          Entity& setType( Type type );
          sizetype value() const;
          Entity& setValue( sizetype value );
        private:
          Type mType;
          sizetype mValue;
      };
    }
  }
}

