#include "texturedshape.hpp"

TexturedShape::TexturedShape() :
texture(NULL),
m_type(sf::Renderer::TriangleFan)
{
};

TexturedShape::TexturedShape(const sf::Image& image) :
texture(&image),
m_type(sf::Renderer::TriangleFan)
{
};

TexturedShape::~TexturedShape()
{
};

void TexturedShape::SetImage(const sf::Image& image)
{
    texture = &image;
}

void TexturedShape::AddPoint(float x, float y, float u, float v, const sf::Color& color)
{
    AddPoint(sf::Vector2f(x, y), sf::Vector2f(u,v), color);
}

void TexturedShape::AddPoint(const sf::Vector2f& position, const sf::Vector2f& texPos, const sf::Color& color)
{
    m_points.push_back(Point(position, texPos, color));
}

unsigned int TexturedShape::GetPointsCount() const
{
    return m_points.size();
}

void TexturedShape::SetPointPosition(unsigned int index, const sf::Vector2f& pos)
{
    m_points[index].position = pos;
}

void TexturedShape::SetPointPosition(unsigned int index, float x, float y)
{
    SetPointPosition(index, sf::Vector2f(x,y));
}

void TexturedShape::SetPointTexturePosition(unsigned int index, const sf::Vector2f& pos)
{
    m_points[index].texturePosition = pos;
}
void TexturedShape::SetPointTexturePosition(unsigned int index, float u, float v)
{
    SetPointTexturePosition(index, sf::Vector2f(u,v));
}

void TexturedShape::SetPointColor(unsigned int index, const sf::Color& col)
{
    m_points[index].color = col;
}


void TexturedShape::SetPrimitiveType(sf::Renderer::PrimitiveType type)
{
    m_type = type;
}

const sf::Vector2f& TexturedShape::GetPointPosition(unsigned int index) const
{
    return m_points[index].position;
}

const sf::Vector2f& TexturedShape::GetPointTexturePosition(unsigned int index) const
{
    return m_points[index].texturePosition;
}

const sf::Color& TexturedShape::GetPointColor(unsigned int index) const
{
    return m_points[index].color;
}

void TexturedShape::Render(sf::RenderTarget& target, sf::Renderer& renderer) const
{
    if(GetPointsCount() > 2){
        renderer.SetTexture(texture);

        renderer.Begin(m_type);
        for(unsigned int i = 0; i < GetPointsCount(); ++i){
            renderer.AddVertex(m_points[i].position.x, m_points[i].position.y,
                               m_points[i].texturePosition.x, m_points[i].texturePosition.y,
                               m_points[i].color);
        }
        renderer.End();
    }
}

TexturedShape::Point::Point(sf::Vector2f pos, sf::Vector2f texturePos, sf::Color col) :
position(pos),
texturePosition(texturePos),
color(col)
{
}
