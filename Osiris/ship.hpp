#ifndef SHIP_HPP_INCLUDED
#define SHIP_HPP_INCLUDED

#include "object.hpp"
#include "shot.hpp"

#include <list>

class Ship : public Object
{
    public:
        Ship();
        virtual ~Ship();

        virtual sf::FloatRect GetRect(void) const;
        void update(const sf::Input &Input, const sf::Vector2f &mousePos, float elapsedTime, std::list<Shot *> &shotList);

        virtual void draw(sf::RenderTarget &target) const;
    private:
        sf::Image m_shipImage;
        sf::Sprite m_sprite;

        float m_timer;

        sf::Image *shotImage;
};

#endif // SHIP_HPP_INCLUDED
