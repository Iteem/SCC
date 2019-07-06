#ifndef ENEMY_HPP_INCLUDED
#define ENEMY_HPP_INCLUDED

#include <list>
#include <boost/property_tree/ptree.hpp>

#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>


typedef std::list<std::pair<sf::Sprite, sf::Vector2f>> BulletList;

class Enemy
{
	public:
		Enemy( sf::Vector2f pos, const boost::property_tree::ptree &config );
		~Enemy();

		bool update( float dt, sf::Vector2f playerPos, BulletList &bullets, BulletList &eBullets );

		void draw( sf::RenderTarget &target ) const;

	private:
		const boost::property_tree::ptree &m_config;

		sf::Sprite m_sprite;
		static thor::ResourceCache<sf::Texture> m_cache;

		float m_rotationSpeed;
		sf::FloatRect m_aabb;

		float m_timer;
		float m_cooldown;
};

#endif // ENEMY_HPP_INCLUDED
