#ifndef CONFIG_HPP_INCLUDED
#define CONFIG_HPP_INCLUDED

#include <string>
#include <map>
#include <sstream>
#include <iostream>

class Config
{
    public:
        Config();
        ~Config();

        bool loadFromFile(const std::string &path);
        bool saveToFile(const std::string &path);

        std::string getStringValue(const std::string &key) const;
		void setStringValue(const std::string &key, const std::string &value);

        //utility templates for automatic conversation between string and any type
		template<typename T>
		bool getValue(std::string key, T &value) const{
			std::stringstream stream;
			stream << getStringValue(key);
			stream >> value;
			if(stream.fail()){
				std::cerr << "Warning: Failed to cast to the requested type from key " << key << "." << std::endl;
				return false;
			};
			return true;
		}

		template<typename T>
		bool setValue(std::string key, T &value){
			std::stringstream stream;
			std::string str;
			stream << value;
			stream >> str;
			if(stream.fail()){
				std::cerr << "Warning: Failed to set value of key " << key << "." << std::endl;
				return false;
			}
			setStringValue(key, str);
			return true;
		}


    private:
        std::map<std::string, std::string> m_map;
};



#endif // CONFIG_HPP_INCLUDED
