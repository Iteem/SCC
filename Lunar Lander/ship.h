#ifndef SHIP_H_INCLUDED
#define SHIP_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Ship
{
    public:
        Ship(sf::RenderWindow&, sf::Vector2f);
        ~Ship(){};
        void Update(float ElapsedTime);
        void Draw(void);
        sf::Vector2f GetPosition(void);
        void SetPosition(sf::Vector2f);
        bool IsPixel(sf::Vector2f);
        void SetOnPlatform(float);
        bool IsOnPlatform(void);
        sf::Vector2f GetSpeed(void);
        float GetRotation(void);
        sf::Vector2f GetSize(void);
        float GetFuel(void);
        int GetLives(void);
        void SetFuel(float);
        void SetLives(int);
    private:
        sf::Image ShipImage, FlameImage;
        sf::Sprite ShipSprite, FlameSprite;
        sf::Vector2f Speed;
        bool ShowFlame;
        sf::RenderWindow &App;
        const sf::Input &Input;
        float InternTimer;
        float FadingTimer;
        bool Fading;
        bool OnPlatform;
        sf::Vector2f NextPos;
        sf::SoundBuffer RocketSoundBuffer, CrashedSoundBuffer;
        sf::Sound RocketSound, CrashedSound;
        float Fuel;
        int Lives;
};

#endif // SHIP_H_INCLUDED
