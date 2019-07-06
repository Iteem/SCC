#ifndef ENTITY_INCLUDED
#define ENTITY_INCLUDED

#include <memory>
#include <string>
#include <vector>

#include "property.hpp"

class Entity
{
	public:
		Entity();
		~Entity();

	private:
		unsigned int id;
};

#endif // ENTITY_INCLUDED
