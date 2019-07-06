#include "object.hpp"

Object::Object()
{
}

Object::~Object()
{
}

bool Object::collide(const Object *object) const
{
    return GetRect().Intersects(object->GetRect());
}
