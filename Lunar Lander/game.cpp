#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <fstream>

#include "game.h"

#include "ship.h"
#include "map.h"

template<typename T> std::string ToString(T);

bool RunGame(sf::RenderWindow &App, sf::Font &Font, std::string &lvl)
{
    std::ifstream LevelFile((std::string("data/levels/")+lvl).c_str(), std::ios::in);
    if(!LevelFile.good())
        return true;

    int MapWidth;
    int MapHeight;
    LevelFile >> MapWidth;
    LevelFile >> MapHeight;

    int hp1, hp2;

    LevelFile >> hp1;
    LevelFile >> hp2;

    sf::Vector2i StartPos(hp1, hp2);

    std::string CharMap;

    while(!LevelFile.eof())
    {
        std::string buffer;
        getline(LevelFile, buffer);
        CharMap += buffer;
    }

    sf::Image BlackRectImage;
    BlackRectImage.Create(160, 100, sf::Color::Black);
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 100; ++j)
        {
            BlackRectImage.SetPixel(i,j, sf::Color(50,50,50));
            BlackRectImage.SetPixel(159-i,j, sf::Color(50,50,50));
        }
        for(int j = 0; j < 160; j++)
        {
            BlackRectImage.SetPixel(j, i, sf::Color(50,50,50));
            BlackRectImage.SetPixel(j, 99-i, sf::Color(50,50,50));
        }
    }
    sf::Sprite BlackRectSprite(BlackRectImage);

    sf::String SpeedString("0", Font, 15);
    SpeedString.SetColor(sf::Color::White);
    sf::String RotationString("0", Font, 15);
    RotationString.SetColor(sf::Color::White);
    sf::String FuelString("100", Font, 15);
    FuelString.SetColor(sf::Color::White);
    sf::String LivesString("5", Font, 15);
    LivesString.SetColor(sf::Color::Red);
    sf::String SpeedNameString("Speed:", Font, 15);
    SpeedNameString.SetColor(sf::Color::White);
    sf::String RotationNameString("Winkel:", Font, 15);
    RotationNameString.SetColor(sf::Color::White);
    sf::String FuelNameString("Tank:", Font, 15);
    FuelNameString.SetColor(sf::Color::White);
    sf::String LiveNameString("Leben:", Font, 15);
    LiveNameString.SetColor(sf::Color::White);

    sf::String GameOverString("Game Over", Font, 30);
    GameOverString.SetColor(sf::Color::White);
    GameOverString.SetCenter((GameOverString.GetRect().Right - GameOverString.GetRect().Left) /2,
                             (GameOverString.GetRect().Bottom - GameOverString.GetRect().Top) /2 + 10);
    sf::String PressEnterString("Enter drücken um fortzufahren...", Font, 15);
    PressEnterString.SetColor(sf::Color::White);
    PressEnterString.SetCenter((PressEnterString.GetRect().Right - PressEnterString.GetRect().Left) /2,
                             (PressEnterString.GetRect().Bottom - PressEnterString.GetRect().Top) / 2 - 20);

    sf::Shape GameOverBackground;

    bool GameOver = false;

    sf::SoundBuffer LowFuelBuffer;
    if(!LowFuelBuffer.LoadFromFile("data/lowfuel.wav"))
        return false;
    sf::Sound LowFuel(LowFuelBuffer);

    bool LowFuelPlayed = false;

    Ship MyShip(App, sf::Vector2f(StartPos.x * 59 + 59 * 0.5f, StartPos.y * 55));
    MyShip.SetOnPlatform(StartPos.y * 55);

    Map MyMap(App, CharMap, MapWidth, MapHeight, 59, 55);
    MyMap.Update(MyShip.GetPosition());

    sf::View View(MyShip.GetPosition(), sf::Vector2f(400, 300));
    App.SetView(View);

    sf::Event Event;

    while(true)
    {
        while(App.GetEvent(Event))
        {
            if(Event.Type == sf::Event::Closed)
                return false;
            if(Event.Type == sf::Event::KeyPressed and Event.Key.Code == sf::Key::Escape)
                return true;
            if(Event.Type == sf::Event::KeyPressed and Event.Key.Code == sf::Key::Return and GameOver)
                return true;
        }

        if(MyShip.GetLives() < 1)
        {
            GameOver = true;
            GameOverString.SetPosition(View.GetCenter());
            PressEnterString.SetPosition(View.GetCenter());
            GameOverBackground = sf::Shape::Rectangle(-400, -300, 400, 300, sf::Color(0,0,0,128));
            GameOverBackground.SetPosition(View.GetCenter());
        }

        float ElapsedTime = App.GetFrameTime();
        if(!GameOver)
        {
            MyShip.Update(ElapsedTime);
            MyMap.Update(MyShip.GetPosition());

            float SpeedHelp = sqrt(pow(MyShip.GetSpeed().y , 2) + pow(MyShip.GetSpeed().x , 2));

            if(!MyShip.IsOnPlatform())
            {
                sf::Vector2i h(static_cast<int>(MyShip.GetPosition().x), static_cast<int>(MyShip.GetPosition().y));

                int RotationHelp;
                if(MyShip.GetRotation() < 180)
                    RotationHelp = static_cast<int>(MyShip.GetRotation()/2.f);
                else
                    RotationHelp = static_cast<int>((MyShip.GetRotation()-360)/2.f*-1);

                if(MyMap.IsOnPlatform(h.x, static_cast<int>(h.y+MyShip.GetSize().y/2)+1+RotationHelp) and (MyShip.GetRotation() <= 8 or MyShip.GetRotation() >= 352))
                {
                    sf::Vector2f Speed = MyShip.GetSpeed();
                    if(Speed.y >= 0 and SpeedHelp <= 80 and MyShip.GetSpeed().y > 0)
                    {

                        MyShip.SetOnPlatform(static_cast<int>(h.y/55)*55+55);
                        if(static_cast<int>(MyShip.GetPosition().x/59) != StartPos.x or static_cast<int>(MyShip.GetPosition().y/55) != StartPos.y)
                        StartPos = sf::Vector2i(static_cast<int>(MyShip.GetPosition().x/59), static_cast<int>(MyShip.GetPosition().y/55+1));
                        LowFuelPlayed = false;
                        if(MyMap.GetTile(static_cast<int>(MyShip.GetPosition().x/59), static_cast<int>(MyShip.GetPosition().y/55)+1) == 'Z')
                        {
                            GameOver = true;
                            GameOverString.SetText("Gewonnen!");
                            GameOverString.SetPosition(View.GetCenter());
                            PressEnterString.SetPosition(View.GetCenter());
                            GameOverBackground = sf::Shape::Rectangle(-400, -300, 400, 300, sf::Color(0,0,0,128));
                            GameOverBackground.SetPosition(View.GetCenter());
                            GameOverString.SetCenter((GameOverString.GetRect().Right - GameOverString.GetRect().Left) /2,
                                                     (GameOverString.GetRect().Bottom - GameOverString.GetRect().Top) /2 + 10);
                        }
                        goto EndFor;
                    }
                }

                for(int i = -22+h.x; i < 22+h.x; i++)
                {
                    for(int j = -22+h.y; j < 22+h.y; j++)
                    {
                        if(MyShip.IsPixel(sf::Vector2f(i, j)) and MyMap.IsPixel(i, j))
                        {
                            MyShip.SetPosition(sf::Vector2f(StartPos.x * 59 + 59 * 0.5f, StartPos.y * 55));
                            goto EndFor;
                        }
                    }
                }
            }
            else
                LowFuelPlayed = false;
            EndFor:

            SpeedString.SetText(ToString(static_cast<int>(SpeedHelp / 10)));
            if(SpeedHelp >= 80)
                SpeedString.SetColor(sf::Color::Red);
            else if(SpeedHelp >= 50)
                SpeedString.SetColor(sf::Color::Yellow);
            else
                SpeedString.SetColor(sf::Color::Green);

            RotationString.SetText(ToString(static_cast<int>(MyShip.GetRotation())));
            if(MyShip.GetRotation() <= 4 or MyShip.GetRotation() >= 356)
                RotationString.SetColor(sf::Color::Green);
            else if(MyShip.GetRotation() <= 8 or MyShip.GetRotation() >= 352)
                RotationString.SetColor(sf::Color::Yellow);
            else
                RotationString.SetColor(sf::Color::Red);

            FuelString.SetText(ToString(static_cast<int>(MyShip.GetFuel())));
            if(MyShip.GetFuel() >= 50)
                FuelString.SetColor(sf::Color::Green);
            else if(MyShip.GetFuel() >= 20)
                FuelString.SetColor(sf::Color::Yellow);
            else
            {
                FuelString.SetColor(sf::Color::Red);
                if(!LowFuelPlayed)
                {
                    if(LowFuel.GetStatus() != sf::Sound::Playing)
                        LowFuel.Play();
                    LowFuelPlayed = true;
                }
            }

            LivesString.SetText(ToString(MyShip.GetLives()));

            View.SetCenter(MyShip.GetPosition());

            BlackRectSprite.SetPosition(View.GetCenter().x - 400, View.GetCenter().y - 300);

            SpeedNameString.SetPosition(View.GetCenter().x - 390 , View.GetCenter().y - 300 + 10 );
            RotationNameString.SetPosition(View.GetCenter().x - 390 , View.GetCenter().y - 300 + 30 );
            FuelNameString.SetPosition(View.GetCenter().x - 390 , View.GetCenter().y - 300 + 50 );
            LiveNameString.SetPosition(View.GetCenter().x - 390 , View.GetCenter().y - 300 + 70 );

            SpeedString.SetPosition(View.GetCenter().x - 250 - SpeedString.GetRect().Right + SpeedString.GetRect().Left , View.GetCenter().y - 300 + 10 );
            RotationString.SetPosition(View.GetCenter().x - 250 - RotationString.GetRect().Right + RotationString.GetRect().Left , View.GetCenter().y - 300 + 30 );
            FuelString.SetPosition(View.GetCenter().x - 250 - FuelString.GetRect().Right + FuelString.GetRect().Left , View.GetCenter().y - 300 + 50 );
            LivesString.SetPosition(View.GetCenter().x - 250 - LivesString.GetRect().Right + LivesString.GetRect().Left , View.GetCenter().y - 300 + 70 );
        }

        App.Clear(sf::Color::Black);

        MyMap.DrawBackground();
        MyShip.Draw();
        MyMap.DrawMap();

        App.Draw(BlackRectSprite);
        App.Draw(SpeedNameString);
        App.Draw(RotationNameString);
        App.Draw(FuelNameString);
        App.Draw(LiveNameString);
        App.Draw(SpeedString);
        App.Draw(RotationString);
        App.Draw(FuelString);
        App.Draw(LivesString);

        if(GameOver)
        {
            App.Draw(GameOverBackground);
            App.Draw(GameOverString);
            App.Draw(PressEnterString);
        }

        App.Display();
    }
}

template<typename T>
std::string ToString(T p)
{
    std::stringstream s;
    s << p;
    return s.str();
}
