#include "config.hpp"

#include <fstream>
#include <iostream>

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
        std::cerr << "Failed to open file \"" << path << "\".";
        return false;
    }

    //delete all old values and keys
    m_map.clear();

    std::string str;
    unsigned int linenum = 0;
    while(file.good()){
        std::getline(file, str);
        linenum++;

        //skip comment and empty lines
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

std::string Config::getValue(const std::string &name) const
{
    std::map<std::string, std::string>::const_iterator it = m_map.find(name);
    if(it == m_map.end()){
        std::cerr << "Warning: " << name << " not set." << std::endl;
        return ""; //value not found, return an empty string
    }else{
        return it->second;
    }
}
