#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include "state.hpp"
#include "map.hpp"
#include "player.hpp"
#include "bomb.hpp"
#include "explosion.hpp"

#include <list>

///maingame class
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
        Map m_map;
        Player m_player1, m_player2;
        std::list< Bomb > m_bombs;
        std::list< Explosion> m_explosions;

        sf::Shape m_gameOverShape;
        sf::Text m_gameOverText;
        bool m_isGameOver;
};

#endif // GAMESTATE_HPP_INCLUDED
