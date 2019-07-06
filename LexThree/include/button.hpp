#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Button
{
    public:
        Button( const std::string &label, sf::Font &font, unsigned int charSize = 50, sf::Color col = sf::Color::White );
        ~Button();

		void setCharacterSize( unsigned int charSize );
        void setColor( sf::Color color );
        void setFont( const sf::Font &font );
        void setPosition( sf::Vector2f pos );
        void setString( const std::string &label );

        bool handleEvent( const sf::Event &event, sf::Vector2f mousePos ); //returns true if pressed
        void update( float elapsedTime );
        void expose( sf::RenderTarget &target ) const;

        static bool loadSound( const std::string &path );

    private:
    	void update();

		static sf::Sound sound;
		static sf::SoundBuffer buffer;

		float m_time;
		bool m_isActive;
        sf::Text m_text;
};

#endif // BUTTON_H_INCLUDED
