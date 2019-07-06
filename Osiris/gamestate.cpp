#include "gameState.hpp"
#include <sstream>

GameState::GameState(Shared &shared) :
State(shared)
{
}

GameState::~GameState()
{
}

void GameState::init(void)
{
    app.ShowMouseCursor(false);

    music.OpenFromFile("data/album2/01 - Merlaska.ogg");
    music.SetLoop(true);
    music.Play();

    backgroundImage.LoadFromFile("data/background.jpg");

    background.SetImage(backgroundImage);
    background.SetOrigin(0, backgroundImage.GetHeight());
    background.SetPosition(192, m_shared.videoMode.Height);

    leftShape = sf::Shape::Rectangle(0, 0, 192, 768, sf::Color::Black);
    rightShape = sf::Shape::Rectangle(832, 0, 192, 768, sf::Color::Black);

    sb.LoadFromFile("data/explosion.wav");
    explosion.SetBuffer(sb);

    papyrus.LoadFromFile("data/papyrus.ttf");

    life = 10;
    score = 0;

    lifeText.SetFont(papyrus);
    lifeText.SetCharacterSize(30);
    lifeText.SetString("Leben: 10");
    lifeText.SetPosition(850, 300);
    lifeText.SetColor(sf::Color::White);

    scoreText.SetFont( font );
    scoreText.SetCharacterSize( 20 );
    scoreText.SetString( "Hello" );
    scoreText.SetPosition( sf::Vector2f( 20, 30 ) );

    scoreText.SetFont(papyrus);
    scoreText.SetCharacterSize(30);
    scoreText.SetString("Score: 0");
    scoreText.SetPosition(850, 400);
    scoreText.SetColor(sf::Color::White);

    gameOver = false;

    gameOverText.SetFont(papyrus);
    gameOverText.SetCharacterSize(50);
    gameOverText.SetString(L"Game Over\n Bitte Escape drücken...");
    gameOverText.SetOrigin(gameOverText.GetRect().Width/2, gameOverText.GetRect().Height/2);
    gameOverText.SetPosition(1024/2, 768/2);
    gameOverText.SetColor(sf::Color::White);

    gameOverShape = sf::Shape::Rectangle(0, 0, 1024, 768, sf::Color(0, 0, 0, 128));

    timer = 0.f;
    totalTime = 0.f;
}

void GameState::destroy(void)
{
    app.ShowMouseCursor(true);
}

void GameState::pause(void)
{
}

void GameState::resume(void)
{
}

State::Next GameState::update(void)
{
    sf::Event event;
    while(app.GetEvent(event)){
        if(event.Type == sf::Event::Closed){
            return State::Quit;
        }
        if(event.Type == sf::Event::KeyPressed){
            if(event.Key.Code == sf::Key::Escape){
                return State::Menu;
            }
        }
    }

    float elapsedTime = app.GetFrameTime();
    const sf::Input &input = app.GetInput();
    sf::Vector2f mousePos(app.ConvertCoords(input.GetMouseX(), input.GetMouseY()));

    if(!gameOver){
        timer += elapsedTime;
        totalTime += timer;
        float tmp = 0.5f + 3.f/((totalTime+300)/300);
        if(timer > tmp){
            enemies.push_back(new Enemy());
            timer -= tmp;
        }

        ship.update(input, mousePos, elapsedTime, shots);
        for(std::list<Enemy *>::iterator it = enemies.begin(); it != enemies.end(); ++it){
            (*it)->update(elapsedTime, enemyShots);
        }

        for(std::list<Shot *>::iterator it = shots.begin(); it != shots.end();){
            (*it)->update(elapsedTime);
            if((*it)->remove){
                delete *it;
                it = shots.erase(it);
            }
            else
                ++it;
        }
        for(std::list<Shot *>::iterator it = enemyShots.begin(); it != enemyShots.end();){
            (*it)->update(elapsedTime);
            if((*it)->collide(&ship)){
                delete *it;
                it = enemyShots.erase(it);
                life--;
                if(life < 1){
                    gameOver = true;
                }
                explosion.Play();
            }else if((*it)->remove){
                delete *it;
                it = enemyShots.erase(it);
            }
            else
                ++it;
        }

        for(std::list<Shot *>::iterator it = shots.begin(); it != shots.end();){
            for(std::list<Enemy *>::iterator it2 = enemies.begin(); it2 != enemies.end();){
                if((*it)->collide(*it2)){
                    delete *it2;
                    it2 = enemies.erase(it2);
                    delete *it;
                    it = shots.erase(it);
                    score += 1;
                    explosion.Play();
                    goto for_goto;
                } else {
                    ++it2;
                }
            }
            ++it;
            for_goto: ;
        }

        std::stringstream str;
        str << life;
        lifeText.SetString("Leben: "+str.str());
        str.str("");
        str << score;
        scoreText.SetString("Score: "+str.str());

        background.Move(0, elapsedTime*3);
    }else{
    }

    return State::NoChange;
}

void GameState::draw(void) const
{
    app.Clear();

    app.Draw(background);

    ship.draw(app);
    for(std::list<Enemy *>::const_iterator it = enemies.begin(); it != enemies.end(); ++it){
        (*it)->draw(app);
    }

    for(std::list<Shot *>::const_iterator it = shots.begin(); it != shots.end(); ++it){
        (*it)->draw(app);
    }
    for(std::list<Shot *>::const_iterator it = enemyShots.begin(); it != enemyShots.end(); ++it){
        (*it)->draw(app);
    }

    app.Draw(leftShape);
    app.Draw(rightShape);

    app.Draw(lifeText);
    app.Draw(scoreText);

    if(gameOver){
        app.Draw(gameOverShape);
        app.Draw(gameOverText);
    }
}
