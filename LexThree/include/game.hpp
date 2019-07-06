#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <memory>

#include "state.hpp"

class Shared;

class Game
{
	public:
		Game(int argc, char **argv);
		~Game();

		int run(void);

	private:
		std::unique_ptr< State > m_state;
		std::unique_ptr< Shared > m_shared;

		void handleSwap( State::Next next );
		bool exit;
};

#endif // GAME_HPP_INCLUDED
