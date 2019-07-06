#include "map.hpp"

#include <fstream>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/spirit/include/qi.hpp>

#include <SFML/Graphics.hpp>
#include <zlib.h>

sf::Uint8 base64_decode_digit(char c) {
	switch(c){
		case '+' :
			return 62;
		case '/' :
			return 63;
		default  :
			if (isdigit(c))
				return c - '0' + 26 + 26;
			else if (islower(c))
				return c - 'a' + 26;
			else if (isupper(c))
				return c - 'A';
			else
				throw std::runtime_error("Invalid Base64 character: " + c);
	}
}

std::vector<sf::Uint8> decompress(const std::vector<sf::Uint8> &src, int expectedSize){
	std::vector<sf::Uint8> dest;

	dest.resize(expectedSize);
    z_stream strm;

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.next_in = (Bytef *) &src[0];
    strm.avail_in = src.size();
    strm.next_out = (Bytef *) &dest[0];
    strm.avail_out = dest.size();

	//use inflateInit2 with 15 + 32 as second parameter to decompress both zlib and gzip formats
    int ret = inflateInit2(&strm, 15 + 32);

    if (ret != Z_OK) {
        throw std::runtime_error("Failed to initialize zlib.");
    }

    do {
        ret = inflate(&strm, Z_SYNC_FLUSH);

        if(ret != Z_OK && ret != Z_STREAM_END){
			throw std::runtime_error("Failed to decompress data.");
        }

        if (ret != Z_STREAM_END) {
            int oldSize = dest.size();
            dest.resize(dest.size() * 2);

            strm.next_out = (Bytef *)(&dest[0] + oldSize);
            strm.avail_out = oldSize;
        }
    }
    while (ret != Z_STREAM_END);

    inflateEnd(&strm);

    //resize the vector to fit the data length exactly
    dest.resize(dest.size() - strm.avail_out);

    return dest;
}

std::vector<sf::Uint8> base64_decode(const std::string &str){
	std::vector<sf::Uint8> vec;

	for(size_t offset = 0; offset + 3 < str.length() ; offset +=4){
		unsigned char a = base64_decode_digit(str[offset]);
		unsigned char b = base64_decode_digit(str[offset+1]);
		vec.push_back((a << 2) | (b >> 4));

		if(str[offset+2] == '=')
			return vec;
		a = b; b = base64_decode_digit(str[offset+2]);
		vec.push_back((a << 4) | (b >> 2));

		if(str[offset+3] == '=')
			return vec;
		a = b; b = base64_decode_digit(str[offset+3]);
		vec.push_back((a << 6) | b);
	}
	return vec;
}

Map::Map()
{
}

Map::~Map()
{
}

bool Map::load( std::string path )
{
	using boost::property_tree::ptree;

	ptree pt;
	read_xml( path, pt );

	// basic attributes
	m_dimension.x =  pt.get<int>( "map.<xmlattr>.width", 0 );
    m_dimension.y =  pt.get<int>( "map.<xmlattr>.height", 0 );
	m_tileDimension.x = pt.get<int>( "map.tileset.<xmlattr>.tilewidth", 0 );
	m_tileDimension.y = pt.get<int>( "map.tileset.<xmlattr>.tileheight", 0 );

	m_startPos.x = pt.get<int>( "map.objectgroup.object.<xmlattr>.x", 0 ) / m_tileDimension.x;
	m_startPos.y = pt.get<int>( "map.objectgroup.object.<xmlattr>.y", 0 ) / m_tileDimension.y;

	// load tileset
	if( !m_texture.loadFromFile( "data/levels/" + pt.get( "map.tileset.image.<xmlattr>.source", "" ) ) ){
		return false;
	}
	m_texture.setSmooth(true);

	// load the map data itself
	std::string data = boost::trim_copy( pt.get<std::string>( "map.layer.data" ) );

	std::string encoding = pt.get<std::string>( "map.layer.data.<xmlattr>.encoding", "" );
	if(encoding == "base64"){
		std::vector<sf::Uint8> vec;
		std::string compression = pt.get<std::string>("map.layer.data.<xmlattr>.compression", "");

		if( compression == "gzip" || compression == "zlib" ){
			std::vector<sf::Uint8> tmp(base64_decode(data));
			vec = decompress(tmp, m_dimension.x * m_dimension.y);
		}
		else {
			vec = base64_decode(data);
		}

		for( size_t i = 0; i + 3 < vec.size(); i += 4 ){
			m_tiles.push_back(vec[i] | vec[i+1] << 8 | vec[i+2] << 16 | vec[i+3] << 24);
		}
	}
	else if ( encoding == "csv" ){
		using namespace boost::spirit;

		std::string::const_iterator first = data.begin();
		std::string::const_iterator last = data.end();
		bool r = qi::phrase_parse(first, last, qi::int_ % ',', ascii::space, m_tiles);

		if(!r || first != last){
			return false;
		}
	}
	else {
		return false;
	}

    Pos = sf::Vector2f(0,0);

    compile();

    return true;
}

void Map::update(sf::Vector2f Position)
{
    if(static_cast<int>(Position.x/m_tileDimension.x) != static_cast<int>(Pos.x/m_tileDimension.x) or static_cast<int>(Position.y/m_tileDimension.y) != static_cast<int>(Pos.y/m_tileDimension.y))
    {
        Pos = Position;
        compile();
    }
    Pos = Position;
}

void Map::draw( sf::RenderTarget &target ) const
{
    for( const sf::Drawable &d : TerrainToDraw )
        target.draw( d );
}

bool Map::isOnPlatform(unsigned int i, unsigned int j)
{
    //char h = CharMap[i/m_tileDimension.x + j/m_tileDimension.y*m_dimension.x];
    //if(h == 'P' or h == 'S' or h == 'Z')
    int h = m_tiles[i/m_tileDimension.x + j/m_tileDimension.y*m_dimension.x];
    if( h > 0 && h <= 3 )
        return true;
    return false;
}

bool Map::isPixel(unsigned int i, unsigned int j)
{
    //if(CharMap[i/m_tileDimension.x + j/m_tileDimension.y*m_dimension.x] != ' ')
    return m_tiles[i/m_tileDimension.x + (j/m_tileDimension.y)*m_dimension.x] != 0;
}

void Map::compile() const
{
    TerrainToDraw.clear();
    sf::Vector2i h(static_cast<int>((Pos.x-1024/2)/m_tileDimension.x-2), static_cast<int>((Pos.y-768/2)/m_tileDimension.y-2));
    sf::Vector2i h2(static_cast<int>((Pos.x+1024/2)/m_tileDimension.x+2), static_cast<int>((Pos.y+768/2)/m_tileDimension.y+2));
    //sf::Sprite tmp;

    sf::Sprite tmp(m_texture);

	unsigned int numberOfColumns = (m_texture.getSize().x - 2) / (m_tileDimension.x+1) + 1;

    for(int i = h.x; i < h2.x; ++i){
        for(int j = h.y; j < h2.y; ++j){
        	int tileID = 1;

        	if(i >= 0 && static_cast<unsigned int>( i ) < m_dimension.x && j >=0 && static_cast<unsigned int>( j ) < m_dimension.y){
            	tileID = m_tiles[i+j*m_dimension.x];
        	}

			if(tileID > 0){
				sf::Vector2i tileOffset((tileID - 1) % numberOfColumns * (m_tileDimension.x + 1) + 1,
										(tileID - 1) / numberOfColumns * (m_tileDimension.y + 1) + 1);
				tmp.setTextureRect( sf::IntRect( tileOffset, static_cast<sf::Vector2i>( m_tileDimension ) ) );
				tmp.setPosition( i * static_cast<int>( m_tileDimension.x ), j * static_cast<int>( m_tileDimension.y ) );
				TerrainToDraw.push_back(tmp);
			}
        }
    }
}

int Map::getTile(unsigned int x, unsigned int y)
{
    if(x >= 0 && x < m_dimension.x && y >= 0 && y < m_dimension.y)
        return m_tiles[x+y*m_dimension.x];
    return 1;
}

sf::Vector2u Map::getStartPos()
{
	return m_startPos;
}

sf::Vector2u Map::getDimension()
{
	return m_dimension;
}

sf::Vector2u Map::getTileDimension()
{
	return m_tileDimension;
}
