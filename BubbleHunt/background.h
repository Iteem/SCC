#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include <SFML/Graphics.hpp>

class Background : public sf::Drawable
{
    public:
        Background(void);
        virtual ~Background(void){};
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::VertexArray water;
        sf::VertexArray sky;
};

#endif // BACKGROUND_H_INCLUDED
