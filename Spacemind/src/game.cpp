#include "game.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "shared.hpp"
#include "state.hpp"
#include "config.hpp"

#include "introstate.hpp"
#include "menustate.hpp"
#include "gamestate.hpp"

Game::Game(int argc, char **argv)
{
}

Game::~Game()
{
}

int Game::run(void)
{
	//load game.ini
    Config config;
    if(!config.loadFromFile("game.ini")){
		std::cerr << "Error: Failed to load game.ini, programm will now exit." << std::endl;
		return 1;
    }

	srand(time(0));

    //set up a window
    int aa = 4;
    config.getValue("antialaising", aa);
    sf::ContextSettings settings;
    settings.AntialiasingLevel = aa;
    sf::VideoMode videoMode(800, 600, 24);
    config.getValue("width", videoMode.Width);
    config.getValue("height", videoMode.Height);
    config.getValue("bpp", videoMode.BitsPerPixel);

    unsigned int style = sf::Style::Default;
    std::string string;
	config.getValue("fullscreen", string);
	if(string == "true"){
		style = sf::Style::Fullscreen;

		config.getValue("setresolution", string);
		//only set resolution if in fullscreen mode
		if(string == "true"){
			sf::VideoMode tmpVM(sf::VideoMode::GetFullscreenModes()[0]);
			videoMode = tmpVM;
			config.setValue("width", tmpVM.Width);
			config.setValue("height", tmpVM.Height);
			config.setValue("bpp", tmpVM.BitsPerPixel);
			config.setStringValue("setresolution", "false");
			config.saveToFile("game.ini");
		}
	}

    sf::RenderWindow app(videoMode, "Spacemind", style, settings);//sf::Style::Fullscreen, settings);
    ///TODO: should be loaded from config-file
    //app.EnableVerticalSync(true);
    app.SetFramerateLimit(60);

    //set up a state
    Shared shared(app, videoMode, config);
    State *state;
    state = new IntroState(shared);//IntroState(shared);

    if(!state->init()){
		std::cerr << "Error: Failed to initialize first state, program will now exit." << std::endl;
		return 1;
	}

    while(true){
        State::Next next = state->update();
        if(next != State::NoChange){ //the state will change
            //destroy the old one
            state->destroy();
            delete state;

            //create and initialize a new state
            switch(next){
                case State::Intro:
                    state = new IntroState(shared);
                    break;
                case State::Menu:
                    state = new MenuState(shared);
                    break;
                case State::Game:
                    state = new GameState(shared);
                    break;
				case State::Quit:
					return 0;
                default:
					//Unknown statetyp, exit
					std::cerr << "Error: Switch to unknown statetyp requested, program will now exit." << std::endl;
                    return 1;
            }

            if(!state->init()){
				std::cerr << "Error: Failed to initialize new state, program will now exit." << std::endl;
				return 1;
            }
        }

		app.Clear();
		state->draw();
		app.Display();
    }
}
