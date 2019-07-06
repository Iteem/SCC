#include "enemy.hpp"

#include <Thor/Vectors.hpp>
#include <Thor/Math.hpp>

thor::ResourceCache<sf::Texture> Enemy::m_cache;

Enemy::Enemy( sf::Vector2f pos, const boost::property_tree::ptree &config ) :
	m_config( config )
{
	auto texture = m_cache.acquire( thor::Resources::fromFile<sf::Texture>( config.get<std::string>( "enemy.texture" ) ) );

	m_sprite.setTexture( *texture );
	m_sprite.setOrigin( config.get( "enemy.originX", 0 ), config.get( "enemy.originY", 0 ) );
	m_sprite.setPosition( pos );
	m_sprite.setRotation( thor::random( 0.f, 360.f ) );

	m_rotationSpeed = config.get( "enemy.rotationspeed", 1.f );

	m_aabb = sf::FloatRect( pos - sf::Vector2f( 14, 10 ), sf::Vector2f( 28, 20 ) );

	m_cooldown = config.get( "enemy.cooldown", 0.5f );
	m_timer = m_cooldown;
}

Enemy::~Enemy()
{
}

bool Enemy::update( float dt, sf::Vector2f playerPos, BulletList &bullets, BulletList &eBullets )
{
	m_timer -= dt;

	// die if player is too far away
	if( thor::squaredLength( playerPos - m_sprite.getPosition() ) > 1000 * 1000 )
		return true;

	sf::Vector2f vec = playerPos - m_sprite.getPosition();
	if( vec != sf::Vector2f( 0.f, 0.f ) ){
		float angle = thor::polarAngle( vec ) - m_sprite.getRotation() + 90.f;
		angle = angle > 180.f ? angle - 360.f : angle < -180.f ? angle + 360.f : angle;
		float sign = angle > 0 ? 1 : -1;

		m_sprite.rotate( sign * std::min( std::abs( angle ), m_rotationSpeed * dt ) );

		// new bullet
		if( std::abs( angle ) < m_rotationSpeed * dt && m_timer < 0.f ){
			m_timer = m_cooldown;

			sf::Sprite tmp( *m_cache.acquire( thor::Resources::fromFile<sf::Texture>( m_config.get<std::string>( "bullet.textureenemy" ) ) ) );
			tmp.setOrigin( static_cast<sf::Vector2f>( tmp.getTexture()->getSize() ) / 2.f );
			tmp.setPosition( m_sprite.getTransform().transformPoint( sf::Vector2f( m_config.get( "enemy.gunposX", 0 ), m_config.get( "enemy.gunposY", 0 ) ) ) );
			tmp.setRotation( m_sprite.getRotation() );

			sf::Vector2f dir =  playerPos - tmp.getPosition();

			if( thor::squaredLength( dir ) > 100.f ) {
				eBullets.emplace_back( tmp, thor::unitVector( dir ) * m_config.get( "bullet.speed", 1000.f ) );
			}
		}
	}

	for( auto it = bullets.begin(); it != bullets.end(); ){
		if( m_aabb.contains( it->first.getPosition() ) ){
			bullets.erase( it );
			return true;
		}
		++it;
	}

	return false;
}

void Enemy::draw( sf::RenderTarget &target ) const
{
	target.draw( m_sprite );
}
