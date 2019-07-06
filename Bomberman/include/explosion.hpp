#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED

#include <SFML/Graphics.hpp>

class Explosion : public sf::Drawable
{
    public:
        Explosion(sf::Vector2i pos);
        ~Explosion();

        void update(float elapsedTime);

        sf::Vector2i getPosition() const;

        bool isDead(void) const;
    private:
        sf::Sprite m_sprite;
        float m_lifetime;
        bool m_isDead;

        sf::Vector2i m_position;

        virtual void Render(sf::RenderTarget& target, sf::Renderer& renderer) const;
};

#endif // EXPLOSION_H_INCLUDED
