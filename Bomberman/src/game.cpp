#include "game.hpp"
#include "config.hpp"

#include "shared.hpp"
#include "state.hpp"
#include "gamestate.hpp"
#include "menustate.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

Game::Game()
{
}

Game::~Game()
{
}

int Game::run(void)
{
    Config config;
    config.loadFromFile("game.ini");

    //load video configurations
    std::stringstream stream;

    sf::VideoMode videoMode;
    getValue(config, "width", videoMode.Width);
    getValue(config, "height", videoMode.Height);
    getValue(config, "bpp", videoMode.BitsPerPixel);

    sf::ContextSettings contextSettings;
    getValue(config, "antialaising", contextSettings.AntialiasingLevel);

    unsigned int style = sf::Style::Default;
    if(config.getValue("fullscreen") == "true")
        style = sf::Style::Fullscreen;

    //set up the window
    sf::RenderWindow app(videoMode, "BomberMan", style, contextSettings);

    if(config.getValue("verticalsync") == "true"){
        app.EnableVerticalSync(true);
    }else{
        int h = 0;
        getValue(config, "framelimit", h);
        app.SetFramerateLimit(h);
    }

    //set up a state
    Shared shared(app, videoMode, config);
    State *state;
    state = new MenuState(shared);
    state->init();

    while(true){
        State::Next next = state->update();
        if(next != State::NoChange){ //the state will change
            //destroy the old one
            state->destroy();
            delete state;

            //create and initialize an new state
            switch(next){
                case State::Menu:
                    state = new MenuState(shared);
                    break;
                case State::Game:
                    state = new GameState(shared);
                    break;
                default:
                    return 0; //State::Quit or unknown statetyp, exit
            }
            state->init();
        }

        state->draw();

        app.Display();
    }
}
