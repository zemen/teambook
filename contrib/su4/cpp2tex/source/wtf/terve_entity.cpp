#include "../../include/wtf/terve_entity.h"

using tamias::wtf::terve::Entity;

Entity::Entity( Entity::Type type, tamias::sizetype value ) : mType(type), mValue(value)
{
}

Entity::Entity( const Entity &entity ) : mType(entity.mType), mValue(entity.mValue )
{
}

Entity& Entity::operator = ( const Entity &entity )
{
  mType = entity.mType;
  mValue = entity.mValue;
  return *this;
}

Entity::~Entity()
{
}

Entity::Type Entity::type() const
{
  return mType;
}

Entity& Entity::setType( Entity::Type type )
{
  mType = type;
  return *this;
}

tamias::sizetype Entity::value() const
{
  return mValue;
}

Entity& Entity::setValue( tamias::sizetype value )
{
  mValue = value;
  return *this;
}

