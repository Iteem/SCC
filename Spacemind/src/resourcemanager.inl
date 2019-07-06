template<typename T>
ResourceManager<T>::ResourceManager()
{
}

template<typename T>
ResourceManager<T>::~ResourceManager()
{
    freeAll();
}

template<typename T>
T* ResourceManager<T>::get(const std::string &path)
{
    typename ResourceMap::iterator it = myResourceMap.find(path);
    T* resource = NULL;
    if(it != myResourceMap.end())
        resource = it->second;
    else
    {
        resource = load(path);
        if(resource == NULL)
            return NULL;
        myResourceMap.insert(typename ResourceMap::value_type(path, resource));
    }
    return resource;
};

template<typename T>
void ResourceManager<T>::free(const std::string &path)
{
    typename ResourceMap::iterator it = myResourceMap.find(path);
    T* resource = NULL;
    if(it != myResourceMap.end())
        resource = it->second;
    if(resource != NULL)
    {
        delete resource;
        myResourceMap.erase(path);
    }
};

template<typename T>
void ResourceManager<T>::freeAll(void)
{
    while(!myResourceMap.empty())
    {
        delete myResourceMap.begin()->second;
        myResourceMap.erase(myResourceMap.begin());
    }
};
