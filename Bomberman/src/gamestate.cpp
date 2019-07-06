#include "gameState.hpp"
#include "map.hpp"

const int ExplosionLength = 5;

GameState::GameState(Shared &shared) :
State(shared)
{
}

GameState::~GameState()
{
}

void GameState::init(void)
{
    m_map.loadFromFile("data/map1.map");
    m_player1.init(sf::Vector2f(40, 40), "data/player1.png");
    m_player2.init(sf::Vector2f(744, 552), "data/player2.png");
    m_player2.setUpKey(sf::Key::W);
    m_player2.setLeftKey(sf::Key::A);
    m_player2.setDownKey(sf::Key::S);
    m_player2.setRightKey(sf::Key::D);
    m_player2.setDropBombKey(sf::Key::Space);

    m_gameOverShape = sf::Shape::Rectangle(0, 0, 800, 600, sf::Color(0, 0, 0, 128));
    m_gameOverText.SetPosition(400, 300);
    m_isGameOver = false;
}

void GameState::destroy(void)
{
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

    if(!m_isGameOver){
        for(std::list< Explosion >::iterator it = m_explosions.begin(); it != m_explosions.end();){
            it->update(elapsedTime);
            if(it->isDead())
                it = m_explosions.erase(it);
            else
                ++it;
        }

        for(std::list< Bomb >::iterator it = m_bombs.begin(); it != m_bombs.end();){
            it->update(elapsedTime);
            if(it->isExploded()){
                for(int i = 0; i < ExplosionLength; ++i){
                    if(m_map.getTile(it->getPosition()+sf::Vector2i(i, 0)) == '.'){
                        m_explosions.push_back(Explosion(it->getPosition()+sf::Vector2i(i, 0)));
                    }else if(m_map.getTile(it->getPosition()+sf::Vector2i(i, 0)) == 'o'){
                        m_explosions.push_back(Explosion(it->getPosition()+sf::Vector2i(i, 0)));
                        m_map.setTile(it->getPosition()+sf::Vector2i(i, 0), '.');
                        break;
                    }else{
                        break;
                    }
                }
                for(int i = 0; i < ExplosionLength; ++i){
                    if(m_map.getTile(it->getPosition()+sf::Vector2i(0, i)) == '.'){
                        m_explosions.push_back(Explosion(it->getPosition()+sf::Vector2i(0, i)));
                    }else if(m_map.getTile(it->getPosition()+sf::Vector2i(0, i)) == 'o'){
                        m_explosions.push_back(Explosion(it->getPosition()+sf::Vector2i(0, i)));
                        m_map.setTile(it->getPosition()+sf::Vector2i(0, i), '.');
                        break;
                    }else{
                        break;
                    }
                }
                for(int i = 0; i < ExplosionLength; ++i){
                    if(m_map.getTile(it->getPosition()+sf::Vector2i(-i, 0)) == '.'){
                        m_explosions.push_back(Explosion(it->getPosition()+sf::Vector2i(-i, 0)));
                    }else if(m_map.getTile(it->getPosition()+sf::Vector2i(-i, 0)) == 'o'){
                        m_explosions.push_back(Explosion(it->getPosition()+sf::Vector2i(-i, 0)));
                        m_map.setTile(it->getPosition()+sf::Vector2i(-i, 0), '.');
                        break;
                    }else{
                        break;
                    }
                }
                for(int i = 0; i < ExplosionLength; ++i){
                    if(m_map.getTile(it->getPosition()+sf::Vector2i(0, -i)) == '.'){
                        m_explosions.push_back(Explosion(it->getPosition()+sf::Vector2i(0, -i)));
                    }else if(m_map.getTile(it->getPosition()+sf::Vector2i(0, -i)) == 'o'){
                        m_explosions.push_back(Explosion(it->getPosition()+sf::Vector2i(0, -i)));
                        m_map.setTile(it->getPosition()+sf::Vector2i(0, -i), '.');
                        break;
                    }else{
                        break;
                    }
                }
                it = m_bombs.erase(it);
            }else{
                ++it;
            }
        }

        if(m_player1.update(elapsedTime, input, m_map, m_bombs, m_explosions)){
            m_gameOverText.SetString("Spieler 2 hat gewonnen!");
            m_gameOverText.SetOrigin(m_gameOverText.GetRect().Width/2.f, m_gameOverText.GetRect().Height/2.f);
            m_isGameOver = true;
        }
        if(m_player2.update(elapsedTime, input, m_map, m_bombs, m_explosions)){
            m_gameOverText.SetString("Spieler 1 hat gewonnen!");
            m_gameOverText.SetOrigin(m_gameOverText.GetRect().Width/2.f, m_gameOverText.GetRect().Height/2.f);
            m_isGameOver = true;
        }
    }

    return State::NoChange;
}

void GameState::draw(void) const
{
    app.Clear();

    app.Draw(m_map);
    for(std::list< Explosion >::const_iterator it = m_explosions.begin(); it != m_explosions.end(); ++it){
        app.Draw(*it);
    }
    for(std::list< Bomb >::const_iterator it = m_bombs.begin(); it != m_bombs.end(); ++it){
        app.Draw(*it);
    }
    app.Draw(m_player1);
    app.Draw(m_player2);

    if(m_isGameOver){
        app.Draw(m_gameOverShape);
        app.Draw(m_gameOverText);
    }
}
