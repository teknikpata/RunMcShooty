#pragma once
#include <string>
#include <map>
#include <stdexcept>
#include <assert.h>

namespace Resources{
    enum class Textures{
        Player,
        Platform,
        Pillar
    };
}

template <class Resource, class Identifier>
class ResourceManager {
    std::map<Identifier, std::unique_ptr<Resource>> resources;
public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    void load(const Identifier id, const std::string& filePath) {
        std::unique_ptr<Resource> resource{new Resource()};
        if(not resource->loadFromFile(filePath))
            throw std::runtime_error("ResourceManager::load, Failed to load " + filePath);
        resources.insert(std::make_pair(id, std::move(resource)));
    }

    Resource& get(const Identifier id) {
        assert(resources.find(id) != resources.end());
        return *resources.at(id);
    }
};
