#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include "state.hpp"
#include "ship.hpp"
#include "shot.hpp"
#include "enemy.hpp"

#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

///class for the game
class GameState : public State
{
    public:
        GameState(Shared &shared);
        virtual ~GameState();

        virtual void init(void);     //load resources
        virtual void destroy(void);  //free resources

        virtual void pause(void);
        virtual void resume(void);

        virtual Next update(void);       //update the state, return the next state
        virtual void draw(void) const;   //draw everything

    private:
        sf::Image backgroundImage;
        sf::Sprite background;

        sf::Music music;

        Ship ship;
        std::list<Shot *> shots;

        std::list<Enemy *> enemies;
        std::list<Shot *> enemyShots;

        sf::Shape leftShape, rightShape;

        sf::SoundBuffer sb;
        sf::Sound explosion;

        int life;
        int score;

        sf::Font papyrus;
        sf::Text lifeText;
        sf::Text scoreText;

        bool gameOver;
        sf::Shape gameOverShape;
        sf::Text gameOverText;

        float timer;
        float totalTime;
};

#endif // GAMESTATE_HPP_INCLUDED
