#ifndef BOMB_HPP_INCLUDED
#define BOMB_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class Bomb : public sf::Drawable
{
    public:
        Bomb(sf::Vector2i pos);
        ~Bomb();

        void update(float elapsedTime);

        sf::Vector2i getPosition() const;

        bool isExploded(void) const;
    private:
        sf::Sprite m_sprite;
        float m_lifetime;
        bool m_isExploded;

        sf::Vector2i m_position;

        virtual void Render(sf::RenderTarget& target, sf::Renderer& renderer) const;
};

#endif // BOMB_HPP_INCLUDED
