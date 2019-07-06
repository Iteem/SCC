#ifndef NORMALSHOT_HPP_INCLUDED
#define NORMALSHOT_HPP_INCLUDED

#include "shot.hpp"
#include <SFML/Graphics.hpp>

class NormalShot : public Shot
{
    public:
        NormalShot(sf::Image const* image, sf::Vector2f pos, sf::Vector2f velocity, sf::Vector2f size = sf::Vector2f(10, 10));
        virtual ~NormalShot();

        virtual sf::FloatRect GetRect(void) const;
        virtual void update(float elapsedTime);

        virtual void draw(sf::RenderTarget &target) const;
    private:
        sf::Sprite m_sprite;

        sf::Vector2f m_velocity;
};

#endif // NORMALSHOT_HPP_INCLUDED
