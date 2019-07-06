#include "button.hpp"

#include <iostream>

#include "texturemanager.hpp"

Button::Button(const sf::Text &text, sf::FloatRect rect, const sf::Texture *texNormal, const sf::Texture *texHover, const sf::Texture *texPressed) :
m_text(text),
m_rect(rect),
m_isPressed(false),
m_mouseIsOver(false),
m_texNormal(texNormal),
m_texHover(texHover),
m_texPressed(texPressed)
{;
	m_box.SetTexture(*texNormal);
	m_box.SetDimension(sf::Vector2i(m_rect.Width, m_rect.Height));

    m_text.SetOrigin(m_text.GetRect().Width/2.f, m_text.GetRect().Height/2.f);
    m_text.SetPosition(m_rect.Left + m_rect.Width/2.f, m_rect.Top + m_rect.Height/2.f);
}

Button::~Button()
{
}

sf::FloatRect Button::getRect(void) const
{
    return m_rect;
}

void Button::setRect(const sf::FloatRect &rect)
{
    m_rect = rect;
}

sf::Text Button::getText(void) const
{
    return m_text;
}

void Button::setText(const sf::Text &text)
{
    m_text = text;
}

void Button::handleEvent(const sf::Event &event, const sf::Vector2f &mousePos)
{
    if(event.Type == sf::Event::MouseButtonReleased and event.MouseButton.Button == sf::Mouse::Left){
        if(m_mouseIsOver){
			m_box.SetTexture(*texManager.get("data/button_hover.png"));
            //m_shape.SetColor(MouseOverColor);
        }else{
			m_box.SetTexture(*texManager.get("data/button.png"));
            //m_shape.SetColor(BackgroundColor);
        }
        m_isPressed = false;
    }else if(event.Type == sf::Event::MouseMoved){
        sf::FloatRect rect;
        rect.Width = m_rect.Width;
        rect.Height = m_rect.Height;
        rect.Left = GetPosition().x - GetOrigin().x;
        rect.Top = GetPosition().y - GetOrigin().y;

        if(rect.Contains(mousePos)){
            if(!m_isPressed)
				m_box.SetTexture(*texManager.get("data/button_hover.png"));
                //m_shape.SetColor(MouseOverColor);
            m_mouseIsOver = true;
        } else {
            if(!m_isPressed)
				m_box.SetTexture(*texManager.get("data/button.png"));
                //m_shape.SetColor(BackgroundColor);
            m_mouseIsOver = false;
        }
    }else if(event.Type == sf::Event::MouseButtonPressed and event.MouseButton.Button == sf::Mouse::Left){
        if(m_mouseIsOver){
			m_box.SetTexture(*texManager.get("data/button_pressed.png"));
            //m_shape.SetColor(PressedColor);
            m_isPressed = true;
        }
    }
}

bool Button::isPressed(void) const
{
    return m_isPressed;
}

bool Button::isMouseOver(void) const
{
	return m_mouseIsOver;
}

void Button::Render(sf::RenderTarget& target, sf::Renderer& renderer) const
{
    target.Draw(m_box);
    target.Draw(m_text);
}
