#include "gameState.hpp"

#include <algorithm>
#include <Thor/Math.hpp>
#include <Thor/Vectors.hpp>

#include "utility.hpp"

GameState::GameState(Shared &shared) :
State(shared)
{
}

GameState::~GameState()
{
}

bool GameState::init()
{
	sf::Vector2f dim( m_shared.screenDim );

	// map
	if( !m_map.load( m_shared.config.get( "game.map", "" ) ) )
		return false;

	// player
	m_playerTexture.loadFromFile( m_shared.config.get( "player.texture", "" ) );
	m_playerTexture.setSmooth( true );
	m_player.setTexture( m_playerTexture );
	m_player.setOrigin( m_shared.config.get( "player.originX", 0 ), m_shared.config.get( "player.originY", 0 ) );

	m_player.setPosition( static_cast<sf::Vector2f>( thor::cwiseProduct( m_map.getStartPos(), m_map.getTileDimension() ) ) );

	velocity = sf::Vector2f( 0.f, 0.f );

	// shots
	m_bulletTex.loadFromFile( m_shared.config.get( "bullet.texture", "" ) );
	m_bulletTex.setSmooth( true );

	// other stuff
	bulletSpeed = m_shared.config.get( "bullet.speed", 1000.f );

	m_crosshairTexture.loadFromFile( m_shared.config.get( "game.crosshairtex", "" ) );
	m_crosshair.setTexture( m_crosshairTexture );
	m_crosshair.setOrigin( static_cast<sf::Vector2f>( m_crosshairTexture.getSize() ) / 2.f );

	app.setMouseCursorVisible( false );

	m_spawnrate = m_shared.config.get( "enemy.spawnrate", 1.f );
	m_spawnClock = 0.f;

	// reset time
	frameClock.restart();
	timeFactorMove = 0.f;

	return true;
}

void GameState::destroy()
{
	app.setMouseCursorVisible( true );
}

void GameState::pause()
{
}

void GameState::resume()
{
}

State::Next GameState::update()
{
	// get elapsed time
	float elapsedTime = frameClock.getElapsedTime().asSeconds();
	frameClock.restart();

	sf::View view = app.getDefaultView();
	view.setCenter( m_player.getPosition() );

	// mouse pointer
	sf::Vector2f mousePos = app.mapPixelToCoords( sf::Mouse::getPosition( app ), view );
	m_crosshair.setPosition( static_cast<sf::Vector2f>( sf::Mouse::getPosition( app ) ) );

	// player movement
	float speed = m_shared.config.get( "player.speed", 1.f );
	sf::Vector2f accDir;

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) ){
		accDir.y -= 1.f;
	}
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) ){
		accDir.y += 1.f;
	}
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) ){
		accDir.x -= 1.f;
	}
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) ){
		accDir.x += 1.f;
	}

	// no key pressed, slow time down
	if( std::abs( accDir.x ) < 0.5f && std::abs( accDir.y ) < 0.5f ){
		timeFactorMove -= 4.f * elapsedTime;
	}
	else {
		velocity = thor::unitVector( accDir ) * speed;
		timeFactorMove += 1.f * elapsedTime;
	}

	// rotate
	// make sure we don't try to calculate the angle if the mouse is over the player itself
	float alpha = m_player.getRotation();
	if( thor::squaredLength( mousePos - m_player.getPosition() ) > 0.01f ){
		m_player.setRotation( thor::polarAngle( mousePos - m_player.getPosition() ) + 90.f );
	}
	float dalpha = std::abs( alpha - m_player.getRotation() );
	dalpha = std::min( dalpha, std::abs( dalpha - 360 ) );

	timeFactorMove = std::min( 1.f, std::max( 0.f, timeFactorMove ) ); // clamp between 0 and 1

	float dt = timeFactorMove * elapsedTime + dalpha * m_shared.config.get( "game.rottimefactor", 1.f ) * elapsedTime;

	// check for collisions
	sf::Vector2f newPos = m_player.getPosition() + velocity * timeFactorMove * elapsedTime;
	sf::Vector2i nextTile = thor::cwiseQuotient( static_cast<sf::Vector2i>( newPos ), static_cast<sf::Vector2i>( m_map.getTileDimension() ) );
	int nextTileId = m_map.getTile( nextTile.x, nextTile.y );
	if( nextTileId != 1 )
		m_player.setPosition( newPos );


	// update map
	m_map.update( m_player.getPosition() );

	// bullets
	static float cooldown = 0.f;
	cooldown -= dt;

	// add new bullets if necessary
	if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) && cooldown < 0.f ){
		cooldown = m_shared.config.get( "bullet.cooldown", 1.f );

		sf::Sprite tmp( m_bulletTex );
		tmp.setOrigin( static_cast<sf::Vector2f>( m_bulletTex.getSize() ) / 2.f );
		tmp.setPosition( m_player.getTransform().transformPoint( sf::Vector2f( m_shared.config.get( "player.gunposX", 0 ), m_shared.config.get( "player.gunposY", 0 ) ) ) );
		tmp.setRotation( m_player.getRotation() );

		sf::Vector2f dir =  mousePos - tmp.getPosition();

		if( thor::squaredLength( dir ) > 100.f ) {
			m_bullets.emplace_back( tmp, thor::unitVector( dir ) * bulletSpeed );
		}
	}

	// update bullets
	for( auto &s : m_bullets ){
		s.first.move( s.second * dt );
	}
	sf::FloatRect rect( m_player.getPosition() - sf::Vector2f( 1000.f, 1000.f ), sf::Vector2f( 2000.f, 2000.f ) );
	m_bullets.remove_if( [=]( const std::pair<sf::Sprite, sf::Vector2f> &s ){ return !rect.contains( s.first.getPosition() ); } );

	//spawn enemies
	m_spawnClock += dt;
	if( m_spawnClock > m_spawnrate && m_enemies.size() < m_shared.config.get( "game.maxEnemies", 10.f ) ){
		sf::Vector2i playerTile = thor::cwiseQuotient( static_cast<sf::Vector2i>( m_player.getPosition() ),
													   static_cast<sf::Vector2i>( m_map.getTileDimension() ) );
		sf::Vector2i spawnTile = sf::Vector2i( thor::random( playerTile.x - 8, playerTile.x + 8), thor::random( playerTile.y - 8, playerTile.y + 8) );

		// check if it is a valid tile and not to near to the player (else try again next frame)
		if( m_map.getTile( spawnTile.x, spawnTile.y ) != 1 && std::abs( spawnTile.x - playerTile.x ) > 3 && std::abs( spawnTile.y - playerTile.y ) > 3 ){
			m_enemies.emplace_back( thor::cwiseProduct( static_cast<sf::Vector2f>( spawnTile ), static_cast<sf::Vector2f>( m_map.getTileDimension() ) ), m_shared.config );
			m_spawnClock = 0.f;
			m_spawnrate *= m_shared.config.get( "enemy.spawnratefactor", 0.99f );
		}
	}

	// update enemies
	for( auto it = m_enemies.begin(); it != m_enemies.end(); ){
		if( it->update( dt, m_player.getPosition(), m_bullets, m_enemyBullets ) ){
			it = m_enemies.erase( it );
		}
		else {
			++it;
		}
	}

	// update enemy bullets
	for( auto &s : m_enemyBullets ){
		s.first.move( s.second * dt );
	}
	m_enemyBullets.remove_if( [=]( const std::pair<sf::Sprite, sf::Vector2f> &s ){ return !rect.contains( s.first.getPosition() ); } );

	// check for player - bullet collisions
	sf::FloatRect aabb = sf::FloatRect( m_player.getPosition() - sf::Vector2f( 14, 10 ), sf::Vector2f( 28, 20 ) );

	for( auto it = m_enemyBullets.begin(); it != m_enemyBullets.end(); ){
		if( aabb.contains( it->first.getPosition() ) ){
			return State::Menu; // TODO: give some feedback instead of jumping right back to the menu
		}
		++it;
	}

	return State::NoChange;
}

State::Next GameState::handleEvent( const sf::Event &event )
{
	if( event.type == sf::Event::Closed )
		return State::Quit;

	if( event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape )
		return State::Menu;

	return State::NoChange;
}

void GameState::draw() const
{
	app.clear();

	sf::View view = app.getDefaultView();
	// the tile map doesn't like a center in between two pixels
	view.setCenter( sf::Vector2f( std::floor( m_player.getPosition().x ), std::floor( m_player.getPosition().y ) ) );
	app.setView( view );

	m_map.draw( app );

	for( const auto& sp : m_bullets )
		app.draw( sp.first );

	for( const auto& sp : m_enemyBullets )
		app.draw( sp.first );

	for( const auto& e : m_enemies )
		e.draw( app );

	app.draw( m_player );

	app.setView( app.getDefaultView() );

	app.draw( m_crosshair );
}
