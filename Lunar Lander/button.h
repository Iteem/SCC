#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>

class Button{
    public:
        Button(sf::RenderWindow &Window, sf::Vector2f Position, std::string Label, int Size = 30, sf::Color Color = sf::Color::Black, sf::Vector2f Scale = sf::Vector2f(1,1));
        Button(sf::RenderWindow &Window, float PositionY, std::string Label, int Size = 30, sf::Color Color = sf::Color::Black, sf::Vector2f Scale = sf::Vector2f(1,1));
        ~Button(){};
        static void SetFont(const sf::Font *Font);
        void SetColor(sf::Color Color);
        void SetPosition(sf::Vector2f SetPosition);
        void SetScale(sf::Vector2f Scale);
        void SetText(std::string Text);
        sf::Vector2f GetSize(void) const;
        bool Update(void); //true when pressed, else false
        void Draw(void);
    private:
        sf::RenderWindow &App;
        static const sf::Font *MyFont;
        sf::String MyString;
        sf::Vector2f MyPosition;
        sf::Vector2f MyScale;
        bool Down;

};

#endif // BUTTON_H_INCLUDED
