#ifndef SHOT_H_INCLUDED
#define SHOT_H_INCLUDED

#include "object.hpp"

class Shot : public Object
{
    public:
        Shot();
        virtual ~Shot();

        virtual sf::FloatRect GetRect(void) const = 0;
        virtual void update(float elapsedTime) = 0;

        virtual void draw(sf::RenderTarget &target) const = 0;

        bool remove;
};

#endif // SHOT_H_INCLUDED
