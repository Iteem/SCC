#include <SFML/Graphics.hpp>
#include <cmath>

#include "ship.h"

const float Pi = 3.14159265;
const float Gravitation = 200.f;
const float Accleration = 500.f;

Ship::Ship(sf::RenderWindow &Window, sf::Vector2f Position) : App(Window), Input(App.GetInput())
{
    ShipImage.LoadFromFile("data/ship.png");
    ShipSprite.SetImage(ShipImage);
    ShipSprite.Scale(0.5f, 0.5f);
    ShipSprite.SetCenter(ShipImage.GetWidth() / 2, ShipImage.GetHeight()/2);
    ShipSprite.SetPosition(Position);

    FlameImage.LoadFromFile("data/flame.png");
    FlameSprite.SetImage(FlameImage);
    FlameSprite.SetCenter(FlameImage.GetWidth()/2, -15);
    FlameSprite.SetPosition(ShipSprite.GetPosition());
    FlameSprite.SetScale(0.6f, 0.6f);
    ShowFlame = false;

    Speed = sf::Vector2f(0, 0);

    InternTimer = 0;
    FadingTimer = 0;
    Fading = false;
    OnPlatform = true;

    Fuel = 100;
    Lives = 5;

    RocketSoundBuffer.LoadFromFile("data/rocketsound.wav");
    RocketSound.SetBuffer(RocketSoundBuffer);
    RocketSound.SetLoop(true);

    CrashedSoundBuffer.LoadFromFile("data/crashed.wav");
    CrashedSound.SetBuffer(CrashedSoundBuffer);
    CrashedSound.SetLoop(false);
}

void Ship::Update(float ElapsedTime)
{
    if(!Fading)
    {
        //const sf::Input &Input= App.GetInput();
        if(!OnPlatform)
        {
            if(Input.IsKeyDown(sf::Key::Left))
            {
                ShipSprite.Rotate(180*ElapsedTime);
                FlameSprite.Rotate(180*ElapsedTime);
            }
            if(Input.IsKeyDown(sf::Key::Right))
            {
                ShipSprite.Rotate(-180*ElapsedTime);
                FlameSprite.Rotate(-180*ElapsedTime);
            }

            InternTimer += ElapsedTime;
            while(InternTimer > 0.05f)
            {
                Speed -= Speed * 0.1f * 0.2f;
                InternTimer -= 0.05f;
            }

            Speed.y += Gravitation * ElapsedTime;

            ShowFlame = false;

        }
        if(Input.IsKeyDown(sf::Key::Up) and Fuel > 0)
        {
            if(OnPlatform)
            {
                ShipSprite.Move(0, -3);
                FlameSprite.SetPosition(ShipSprite.GetPosition());
            }
            Speed.y += cos(ShipSprite.GetRotation()/180*Pi) * ElapsedTime * -Accleration; //Bad, its FPS dependent(more Frame-> minimal greater Accleration)
            Speed.x += sin(ShipSprite.GetRotation()/180*Pi) * ElapsedTime * -Accleration;
            ShowFlame = true;
            OnPlatform = false;

            Fuel -= ElapsedTime * 10;
            if(Fuel < 0)
                Fuel = 0;

            if(RocketSound.GetStatus() == sf::Sound::Paused or RocketSound.GetStatus() == sf::Sound::Stopped)
                RocketSound.Play();
        }
        else
        {
            if(RocketSound.GetStatus() == sf::Sound::Playing)
                RocketSound.Pause();
        }
        if(!OnPlatform)
        {
            ShipSprite.Move(Speed.x * ElapsedTime, Speed.y * ElapsedTime);
            FlameSprite.SetPosition(ShipSprite.GetPosition());
        }
    }
    else
    {
        FadingTimer += ElapsedTime;
        if(FadingTimer > 1.f)
        {
            ShipSprite.SetPosition(NextPos);
            FlameSprite.SetPosition(NextPos);
            Fading = false;
            FadingTimer = 0;
            ShipSprite.SetColor(sf::Color(255,255,255,255));
            SetOnPlatform(NextPos.y);
            Lives--;
        }
        else
        {
            sf::Color tmp(255,255,255,static_cast<int>(255-255*FadingTimer));
            ShipSprite.SetColor(tmp);
        }
    }

}

void Ship::Draw(void)
{
    App.Draw(ShipSprite);
    if(ShowFlame)
        App.Draw(FlameSprite);
}

sf::Vector2f Ship::GetPosition(void)
{
    return ShipSprite.GetPosition();
}

void Ship::SetPosition(sf::Vector2f Position)
{
    NextPos = Position;
    Speed.x = 0;
    Speed.y = 0;
    Fading = true;
    ShowFlame = false;
    if(RocketSound.GetStatus() == sf::Sound::Playing)
        RocketSound.Pause();
    if(CrashedSound.GetStatus() != sf::Sound::Playing)
        CrashedSound.Play();
}

bool Ship::IsPixel(sf::Vector2f Position)
{
    sf::Vector2f h = ShipSprite.TransformToLocal(Position);
    if(h.x > 0 and h.x < ShipImage.GetWidth() and h.y > 0 and h.y < ShipImage.GetHeight())
    {
        if(ShipSprite.GetPixel(static_cast<int>(h.x), static_cast<int>(h.y)).a > 10)
            return true;
    }
    return false;
}

void Ship::SetOnPlatform(float Hight)
{
    if(!Fading)
    {
        ShowFlame = false;
        OnPlatform = true;
        Speed.x = 0;
        Speed.y = 0;
        ShipSprite.SetRotation(0);
        FlameSprite.SetRotation(0);
        ShipSprite.SetY(Hight-ShipSprite.GetSize().y/2);
        FlameSprite.SetY(ShipSprite.GetPosition().y);
        Fuel = 100;
        if(RocketSound.GetStatus() == sf::Sound::Playing)
            RocketSound.Pause();
    }
}

bool Ship::IsOnPlatform(void)
{
    return OnPlatform;
}

sf::Vector2f Ship::GetSpeed(void)
{
    return Speed;
}

float Ship::GetRotation(void)
{
    return ShipSprite.GetRotation();
}

sf::Vector2f Ship::GetSize(void)
{
    return ShipSprite.GetSize();
}

float Ship::GetFuel(void)
{
    return Fuel;
}

int Ship::GetLives(void)
{
    return Lives;
}

void Ship::SetFuel(float f)
{
    Fuel = f;
}
void Ship::SetLives(int l)
{
    Lives = l;
}
