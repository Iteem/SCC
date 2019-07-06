#ifndef BEZIERCURVE_HPP_INCLUDED
#define BEZIERCURVE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "texturedshape.hpp"

class BezierCurve : public sf::Drawable
{
    public:
        BezierCurve(sf::Vector2f P0, sf::Vector2f P1, sf::Vector2f P2, sf::Vector2f P3, float thickness = 10.f,
                    unsigned int steps = 20, sf::Image const *texture = NULL, unsigned int iterations = 1);
        ~BezierCurve();

        void SetPoint(unsigned int index, sf::Vector2f position);
        void SetThickness(float thickness);

        void SetSteps(unsigned int steps);
        void SetIterations(unsigned int iterations);

        void SetColor(sf::Color color);
        void SetTexture(sf::Image const *texture);
    private:
        virtual void Render(sf::RenderTarget& target, sf::Renderer& renderer) const;
        void compile();

        sf::Vector2f m_points[4];
        float m_thickness;

        unsigned int m_steps;
        unsigned int m_iterations;

        TexturedShape *m_tshape;
        sf::Image const *m_texture;
        sf::Color m_color;
};

#endif // BEZIERCURVE_HPP_INCLUDED
