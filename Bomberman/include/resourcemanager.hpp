#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <string>

template<class T>
class ResourceManager
{
    public:
        typedef std::map<std::string, T*> ResourceMap;

        ResourceManager();
        virtual ~ResourceManager();

        T* get(const std::string &path);
        void free(const std::string &path);
        void freeAll(void);

    private:
        ResourceMap myResourceMap;
        virtual T* load(const std::string &path) = 0;
};

#include "resourcemanager.inl"

#endif // RESOURCEMANAGER_H
