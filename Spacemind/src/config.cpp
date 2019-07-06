#include "config.hpp"

#include <fstream>
#include <iostream>
#include <list>

Config::Config()
{
}

Config::~Config()
{
}

bool Config::loadFromFile(const std::string &path)
{
    std::ifstream file(path.c_str());
    if(!file.good()){
        std::cerr << "Failed to open file \"" << path << "\"." << std::endl;
        return false;
    }

    //delete all old values and keys
    m_map.clear();

    std::string str;
    unsigned int linenum = 0;
    while(file.good()){
        std::getline(file, str);
        linenum++;

        //skip comments and empty lines
        if(str[0] == ';' or str.empty()){
            continue;
        }

        size_t pos = str.find('=');
        if(pos == std::string::npos){
            std::cerr << path << " " << linenum << ": Equality sign missing." << std::endl;
            continue;
        }

        std::string key(str.substr(0, pos));
        std::string value(str.substr(pos+1));

        if(key.empty()){
            std::cerr << path << " " << linenum << ": Key missing." << std::endl;
            continue;
        }
        if(value.empty()){
            std::cerr << path << " " << linenum << ": Value missing." << std::endl;
            continue;
        }

        //everything ok, add the element to the map
        m_map[key] = value;
    }

    return true;
}

bool Config::saveToFile(const std::string &path)
{
	std::string tmpPath(path + ".tmp");

	std::ifstream oldFile(path.c_str());
	std::ofstream newFile(tmpPath.c_str());

	std::map<std::string, std::string> tmpMap(m_map);

    if(oldFile.good()){
		std::string str;
		unsigned int linenum = 0;
		while(oldFile.good()){
			if(linenum > 0)
				newFile << std::endl;

			std::getline(oldFile, str);
			linenum++;

			//leave comments and empty lines
			if(str[0] == ';' || str.empty()){
				newFile << str;
				continue;
			}

			//find pairs and update them
			size_t pos = str.find('=');
			if(pos == std::string::npos){
				newFile << str;
				continue;
			}

			std::string key(str.substr(0, pos));

			if(key.empty()){
				newFile << str;
				continue;
			}

			newFile << key << "=" << getStringValue(key);

			tmpMap.erase(key);
		}
    } else {
        std::cerr << "Failed to open file \"" << path << "\"." << std::endl;
    }

	for(std::map<std::string, std::string>::iterator it = tmpMap.begin(); it != tmpMap.end(); ++it){
		newFile << std::endl << it->first << "=" << it->second;
	}

	oldFile.close();
	newFile.close();

	std::remove(path.c_str());
	std::rename(tmpPath.c_str(), path.c_str());

	return true;
}

std::string Config::getStringValue(const std::string &key) const
{
    std::map<std::string, std::string>::const_iterator it = m_map.find(key);
    if(it == m_map.end()){
        std::cerr << "Warning: Value of " << key << " requested but not set." << std::endl;
        return ""; //value not found, return an empty string
    }else{
        return it->second;
    }
}

void Config::setStringValue(const std::string &key, const std::string &value)
{
	m_map[key] = value;
}
