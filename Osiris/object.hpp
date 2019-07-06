#ifndef OBJECT_HPP_INCLUDED
#define OBJECT_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class Object
{
    public:
        Object();
        virtual ~Object();

        bool collide(const Object *object) const;
        virtual sf::FloatRect GetRect(void) const = 0;

        virtual void draw(sf::RenderTarget &target) const = 0;
};

#endif // OBJECT_HPP_INCLUDED
