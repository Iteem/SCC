#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>

#include "spritebox.hpp"

class Button : public sf::Drawable
{
    public:
        Button(const sf::Text &text, sf::FloatRect rect, const sf::Texture *texNormal, const sf::Texture *texHover, const sf::Texture *texPressed);
        ~Button();

        sf::FloatRect getRect(void) const;
        void setRect(const sf::FloatRect &rect);

        sf::Text getText(void) const;
        void setText(const sf::Text &text);

        void handleEvent(const sf::Event &event, const sf::Vector2f &mousePos);

        bool isMouseOver(void) const;
        bool isPressed(void) const;
    private:
        virtual void Render(sf::RenderTarget& target, sf::Renderer& renderer) const;

        Spritebox m_box;
        sf::Text m_text;

        sf::FloatRect m_rect;
        int m_border;

        bool m_isPressed;
        bool m_mouseIsOver;

        const sf::Texture *m_texNormal, *m_texHover, *m_texPressed;
};

#endif // BUTTON_HPP_INCLUDED
