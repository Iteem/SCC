#include <SFML/Graphics.hpp>
#include <list>
#include <sstream>

#include "background.h"
#include "player.h"
#include "enemie.h"
#include "weapon.h"
#include "enemieweapon.h"

enum Side
{
    Start,
    Main,
    End
};

int main(void)
{
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "BubbleHunt");//, sf::Style::Fullscreen);
    App.setVerticalSyncEnabled(true);

    sf::Font font;
    font.loadFromFile("data/foo.ttf");
    sf::Text scoreText("Score: 0", font, 50);
    scoreText.setPosition(10, 10);

    sf::Text startText("Zum Starten Taste druecken...", font, 50);
    startText.setPosition(50, 275);

    sf::Text endText("", font, 50);
    endText.setPosition(140, 275);

    Side curSide = Start;

    float score = 0;

    EnemieWeapon::init();
    std::list<EnemieWeapon> enemieWeapons;

    Enemie::init();
    std::list<Enemie> enemies;

    Weapon::init();
    std::list<Weapon> weapons;

    Player player;

    Background background;

    sf::Clock weaponClock;
    sf::Clock frameClock;
    float time = 0;

    while(App.isOpen())
    {
        sf::Event Event;
        while(App.pollEvent(Event))
        {
            if(Event.type == sf::Event::Closed)
                App.close();
            if(Event.type == sf::Event::KeyPressed)
            {
                if(curSide == Start)
                    curSide = Main;
                if(curSide == End)
                    App.close();
            }
        }

        float elapsedTime = frameClock.restart().asSeconds();

        switch(curSide)
        {
        case Main:
            player.update( elapsedTime,
                           App.mapPixelToCoords( sf::Mouse::getPosition(App) ).x );
            time += elapsedTime;
            while(time > 1.f/50.f)
            {
                if(sf::Randomizer::Random(1, 150) == 42)
                {
                    float speed = sf::Randomizer::Random(50, 100);
                    float XPos = sf::Randomizer::Random(350, 550);
                    if(sf::Randomizer::Random(0, 1))
                        enemies.push_back(Enemie(XPos, speed, FromLeft));
                    else
                        enemies.push_back(Enemie(XPos, speed, FromRight));
                }
                for(std::list<Enemie>::iterator it = enemies.begin(); it != enemies.end(); it++)
                {
                    if(sf::Randomizer::Random(1, 200) == 42)
                        enemieWeapons.push_back(EnemieWeapon(it->GetPos(), sf::Vector2f(sf::Randomizer::Random(-20, 20),
                                                                                        sf::Randomizer::Random(-125, -150))));
                }
                time -= 1.f/50.f;
            }
            if(App.GetInput().IsMouseButtonDown(sf::Mouse::Left) and weaponClock.GetElapsedTime() > 1.5f)
            {
                weapons.push_back(Weapon(player.GetPos()));
                weaponClock.Reset();
            }
            for(std::list<Enemie>::iterator it = enemies.begin(); it != enemies.end();)
            {
                it->update(elapsedTime);
                if(it->GetPos().x > 850 or it->GetPos().x < -50)
                    it = enemies.erase(it);
                else
                    ++it;
            }
            for(std::list<Weapon>::iterator it = weapons.begin(); it != weapons.end();)
            {
                it->update(elapsedTime);
                if(it->GetY() > 650)
                    it = weapons.erase(it);
                else
                    ++it;
            }
            for(std::list<EnemieWeapon>::iterator it = enemieWeapons.begin(); it != enemieWeapons.end();)
            {
                it->update(elapsedTime);
                if( it->coolide(player) )
                {
                    curSide = End;
                    std::stringstream str;
                    str << "Game Over   Score: " << score;
                    endText.SetString(str.str());
                }
                if(it->GetPos().y < 205)
                    it = enemieWeapons.erase(it);
                else
                    ++it;
            }

            for(std::list<Enemie>::iterator i = enemies.begin(); i != enemies.end();)
            {
                for(std::list<Weapon>::iterator j = weapons.begin(); j != weapons.end();)
                {
                    if(j->coolide(*i))
                    {
                        weapons.erase(j);
                        i = enemies.erase(i);
                        score++;
                        std::stringstream str;
                        str << "Score: " << score;
                        scoreText.SetString(str.str());
                        goto for_loop;
                    }
                    ++j;
                }
                ++i;
                for_loop:;
            }
            break;
        case Start:
            break;
        case End:
            break;
        }

        App.Clear();

        switch(curSide)
        {
        case Main:
            App.Draw(background);
            for(std::list<Weapon>::iterator it = weapons.begin(); it != weapons.end(); ++it)
                App.Draw(*it);
            for(std::list<Enemie>::iterator it = enemies.begin(); it != enemies.end(); ++it)
                App.Draw(*it);
            for(std::list<EnemieWeapon>::iterator it = enemieWeapons.begin(); it != enemieWeapons.end(); ++it)
                App.Draw(*it);
            App.Draw(player);
            App.Draw(scoreText);
            break;
        case Start:
            App.Draw(startText);
            break;
        case End:
            App.Draw(endText);
            break;
        }

        App.Display();
    }
}
