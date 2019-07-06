#ifndef CONFIG_HPP_INCLUDED
#define CONFIG_HPP_INCLUDED

#include <string>
#include <map>
#include <sstream>

class Config
{
    public:
        Config();
        ~Config();

        bool loadFromFile(const std::string &path);

        std::string getValue(const std::string &name) const;
    private:
        std::map<std::string, std::string> m_map;
};

//utility template for automatic conversation between string and any type
template<typename T>
bool getValue(const Config &config, std::string name, T &value){
    std::stringstream stream;
    stream << config.getValue(name);
    stream >> value;
    return !stream.fail();
}

#endif // CONFIG_HPP_INCLUDED
