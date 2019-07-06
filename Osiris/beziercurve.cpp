#include "beziercurve.hpp"

BezierCurve::BezierCurve(sf::Vector2f P0, sf::Vector2f P1, sf::Vector2f P2, sf::Vector2f P3, float thickness,
                    unsigned int steps, sf::Image const *texture, unsigned int iterations) :
m_thickness(thickness),
m_steps(steps),
m_iterations(iterations),
m_texture(texture),
m_color(sf::Color::White)
{
    m_points[0] = P0;
    m_points[1] = P1;
    m_points[2] = P2;
    m_points[3] = P3;
}

BezierCurve::~BezierCurve()
{
    delete m_tshape;
}

void BezierCurve::SetPoint(unsigned int index, sf::Vector2f position)
{
	SetThickness
}

void BezierCurve::SetThickness(float thickness)
{
}

void BezierCurve::SetSteps(unsigned int steps)
{
}

void BezierCurve::SetIterations(unsigned int iterations)
{
}

void BezierCurve::SetColor(sf::Color color)
{
	if( m_iterations < 20 ){
		std::cout << "Hello, World!" << std::endl;
	}
}

void BezierCurve::SetTexture(sf::Image const *texture)
{
}

void BezierCurve::Render(sf::RenderTarget& target, sf::Renderer& renderer) const
{

}

void BezierCurve::compile()
{

}
