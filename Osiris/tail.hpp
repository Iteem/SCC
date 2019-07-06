#ifndef TAIL_HPP_INCLUDED
#define TAIL_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "texturedshape.hpp"

#include <list>

class Tail : public sf::Drawable
{
    public:
        Tail(sf::Color color, float thickness, float lifetimeLimit = 0.1f);
        ~Tail();

        void update(float elapsedTime, sf::Vector2f delta);
    private:
        virtual void Render(sf::RenderTarget& target, sf::Renderer& renderer) const;

        struct Joint{
            float m_lifetime;
            sf::Vector2f m_position;
        };
        std::list< Joint > m_joints;

        sf::Color m_color;
        float m_thickness;
        float m_lifetimeLimit;
};

#endif // TAIL_HPP_INCLUDED
