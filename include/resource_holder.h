#pragma once
#ifndef resources_holder_h
#define resources_holder_h

#include <cassert>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

template <typename Resource, typename Identifier>
class ResourceHolder {
public:
    void load(Identifier id, const std::string& filename);

    template <typename Parameter>
    void load(Identifier id, const std::string& filename, const Parameter& secondParam);

    Resource& get(Identifier id);
    const Resource& get(Identifier id) const;

    static ResourceHolder& Instance(){
        static ResourceHolder instance;
        return instance;
    }

private:
    ResourceHolder() = default;
    ResourceHolder(const ResourceHolder&) = default;
    ResourceHolder operator=(ResourceHolder other) = delete;
    void insertResource(Identifier id, std::unique_ptr<Resource> resource);

    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include "resource_holder.tcc"

#endif