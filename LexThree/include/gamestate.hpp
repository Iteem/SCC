#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include "state.hpp"

#include <list>
#include <utility>

#include <SFML/Graphics.hpp>

#include "map.hpp"
#include "enemy.hpp"

///class for the game
class GameState : public State
{
	public:
		GameState(Shared &shared);
		virtual ~GameState();

		virtual bool init();	 //load resources
		virtual void destroy();  //free resources

		virtual void pause();
		virtual void resume();

		virtual Next update();  //update the state, return the next state
		virtual Next handleEvent( const sf::Event &event );  //handle a SFML-event
		virtual void draw() const; //draw everything

	private:
		sf::Texture m_playerTexture;
		sf::Sprite m_player;

		std::list<Enemy> m_enemies;
		float m_spawnrate;
		float m_spawnClock;

		sf::Texture m_crosshairTexture;
		sf::Sprite m_crosshair;

		Map m_map;

		sf::Clock frameClock;

		sf::Vector2f velocity;
		float bulletSpeed;
		float timeFactorMove;

		sf::Texture m_bulletTex;
		BulletList m_bullets;
		BulletList m_enemyBullets;
};

#endif // GAMESTATE_HPP_INCLUDED
