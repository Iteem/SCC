#include <SFML/Graphics.hpp>

#include "button.h"

const sf::Font *Button::MyFont;

Button::Button(sf::RenderWindow &Window, sf::Vector2f Position, std::string Label, int Size, sf::Color Color, sf::Vector2f Scale) : App(Window), MyString(Label, *MyFont, Size)
{
    MyString.Scale(Scale);
    MyString.SetPosition(Position);
    MyString.SetColor(Color);
    MyPosition = Position;
    MyScale = Scale;
    Down = false;
}

Button::Button(sf::RenderWindow &Window, float PositionY, std::string Label, int Size, sf::Color Color, sf::Vector2f Scale) : App(Window), MyString(Label, *MyFont, Size)
{
    MyString.Scale(Scale);

    float PositionX = (800 / 2) - ((MyString.GetRect().Right - MyString.GetRect().Left) / 2);

    MyString.SetPosition(PositionX, PositionY);
    MyString.SetColor(Color);
    MyPosition = sf::Vector2f(PositionX, PositionY);
    MyScale = Scale;
    Down = false;
}

void Button::SetPosition(sf::Vector2f Position)
{
    MyString.SetPosition(Position);
    MyPosition = Position;
}

void Button::SetFont(const sf::Font *Font)
{
    MyFont = Font;
}

void Button::SetColor(sf::Color Color)
{
    MyString.SetColor(Color);
}

void Button::SetScale(sf::Vector2f Scale)
{
    MyString.SetScale(Scale);
    MyScale = Scale;
}

sf::Vector2f Button::GetSize(void) const
{
    return sf::Vector2f(MyString.GetRect().Right - MyString.GetRect().Left, MyString.GetRect().Bottom - MyString.GetRect().Top);
}

bool Button::Update(void) //true when pressed, else false
{
    const sf::Input &Input = App.GetInput();
    bool LeftMouseButton = Input.IsMouseButtonDown(sf::Mouse::Left);

    sf::Vector2f MousePos = App.ConvertCoords(App.GetInput().GetMouseX(), App.GetInput().GetMouseY());

    if(MyString.GetRect().Left < MousePos.x and MousePos.x < MyString.GetRect().Right and MyString.GetRect().Top < MousePos.y and MousePos.y < MyString.GetRect().Bottom)
    {
        if (!LeftMouseButton and Down)
        {
            Down = false;
            MyString.SetScale(1.0f * MyScale);
            MyString.SetPosition(MyPosition);
            return true;
        }
        MyString.SetScale(1.5f * MyScale);
        MyString.SetPosition(MyPosition.x - ((MyString.GetRect().Right-MyString.GetRect().Left) / 6), MyPosition.y - ((MyString.GetRect().Bottom-MyString.GetRect().Top)/ 6));
    }
    else
    {
        MyString.SetScale(1.0f * MyScale);
        MyString.SetPosition(MyPosition);
    }

    Down = LeftMouseButton;
    return false;
}

void Button::Draw(void)
{
    App.Draw(MyString);
}

void Button::SetText(std::string Text)
{
    MyString.SetText(Text);
    float PositionX = (800 / 2) - ((MyString.GetRect().Right - MyString.GetRect().Left) / 2);
    MyString.SetX(PositionX);
    MyPosition.x = (PositionX);
}
