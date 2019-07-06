#ifndef TEXTUREDSHAPE_HPP_INCLUDED
#define TEXTUREDSHAPE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>

class TexturedShape : public sf::Drawable
{
    public:
        TexturedShape();
        TexturedShape(const sf::Image& image);
        ~TexturedShape();

        void SetImage(const sf::Image& image);

        void AddPoint(float x, float y, float u = 0.f, float v = 0.f, const sf::Color& color = sf::Color::White);
        void AddPoint(const sf::Vector2f& position, const sf::Vector2f& texPos = sf::Vector2f(0,0),
                      const sf::Color& color = sf::Color(255, 255, 255));

        unsigned int GetPointsCount() const;

        void SetPointPosition(unsigned int index, const sf::Vector2f& pos);
        void SetPointPosition(unsigned int index, float x, float y);

        void SetPointTexturePosition(unsigned int index, const sf::Vector2f& pos);
        void SetPointTexturePosition(unsigned int index, float u, float v);

        void SetPointColor(unsigned int index, const sf::Color& col);

        void SetPrimitiveType(sf::Renderer::PrimitiveType type);

        const sf::Vector2f& GetPointPosition(unsigned int index) const;
        const sf::Vector2f& GetPointTexturePosition(unsigned int index) const;
        const sf::Color& GetPointColor(unsigned int index) const;

    private:
        virtual void Render(sf::RenderTarget& target, sf::Renderer& renderer) const;

        sf::Image const *texture;

        sf::Renderer::PrimitiveType m_type;

        struct Point
        {
            Point(sf::Vector2f pos, sf::Vector2f texturePos, sf::Color col);
            sf::Vector2f position;
            sf::Vector2f texturePosition;
            sf::Color    color;
        };
        std::vector<Point> m_points;
};

#endif // TEXTUREDSHAPE_HPP_INCLUDED
