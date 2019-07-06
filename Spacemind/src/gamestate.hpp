#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <list>
#include <vector>

#include "button.hpp"
#include "spritebox.hpp"
#include "state.hpp"

///class for the game
class GameState : public State
{
    public:
        GameState(Shared &shared);
        virtual ~GameState();

        virtual bool init(void);     //load resources
        virtual void destroy(void);  //free resources

        virtual Next update(void);       //update the state, return the next state
        virtual void draw(void) const;   //draw everything

    private:
		sf::Sprite m_background;

		Spritebox m_field;

		std::vector<Spritebox> m_lines;
		std::vector< std::vector<sf::Sprite> > m_holes;
		std::vector< std::list<sf::Sprite> > m_lights;
		std::vector<sf::Sprite> m_balls;
		std::vector<sf::Sprite> m_solution;

		unsigned int m_curLine;
		unsigned int m_curColumn;
		bool m_lineIsFilled;
		bool m_gameIsOver;

		Button *m_OKButton;
		bool m_OKButtonPressed;
		Button *m_resetButton;
		bool m_resetButtonPressed;
};

#endif // GAMESTATE_HPP_INCLUDED
