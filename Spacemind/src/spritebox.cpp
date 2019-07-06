#include "spritebox.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

Spritebox::Spritebox() :
m_subRect(0, 0, 1, 1),
m_dimension(0, 0)
{
}

void Spritebox::SetTexture(const sf::Texture &texture, bool adjustSubRect)
{
	m_texture = &texture;
	if(adjustSubRect){
        m_subRect = sf::IntRect(0, 0, m_texture->GetWidth(), m_texture->GetHeight());
	}
}

const sf::Texture *Spritebox::GetTexture() const
{
    return m_texture;
}

void Spritebox::SetSubRect(sf::IntRect subRect)
{
    m_subRect = subRect;
}

const sf::IntRect &Spritebox::GetSubRect() const
{
    return m_subRect;
}

void Spritebox::SetDimension(const sf::Vector2i &vec)
{
    m_dimension = vec;
}

const sf::Vector2i &Spritebox::GetDimension() const
{
    return m_dimension;
}

void Spritebox::Render(sf::RenderTarget& target, sf::Renderer& renderer) const
{
    if(m_dimension.x < 1 || m_dimension.y < 1 || m_texture == 0)
        return;

    //round for pixel perfect rendering
    sf::Vector2f step(std::floor(static_cast<float>(m_texture->GetWidth())/3.f + 0.5f),
                      std::floor(static_cast<float>(m_texture->GetHeight())/3.f + 0.5f));

    sf::Vector2f coords[4];
    coords[0] = sf::Vector2f(0, 0);
    coords[1] = step;
    coords[2] = static_cast<sf::Vector2f>(m_dimension) - step;
    coords[3] = static_cast<sf::Vector2f>(m_dimension);

    renderer.SetTexture(m_texture);

    for(unsigned int x = 0; x < 3; ++x){
        renderer.Begin(sf::Renderer::TriangleStrip);
        for(unsigned int y = 0; y < 4; ++y){
            renderer.AddVertex(coords[x].x,   coords[y].y,     x/3.f, y/3.f, sf::Color::White);
            renderer.AddVertex(coords[x+1].x, coords[y].y, (x+1)/3.f, y/3.f, sf::Color::White);
        }
        renderer.End();
    }
}
