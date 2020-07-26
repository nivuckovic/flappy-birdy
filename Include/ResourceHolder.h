#pragma once

#include <map>
#include <memory>
#include <string>
#include <utility>

#include "Enums.h"
#include "SFML/Graphics.hpp"

template <typename Resource, typename Identifier>
class ResourceHolder {
public:
	void load(Identifier id, const std::string& filename);

	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;

private:
	std::map<Identifier, std::unique_ptr<Resource>> m_resourceMap;
};

typedef ResourceHolder<sf::Texture, ID::Textures> TextureHolder;
typedef ResourceHolder<sf::Font, ID::Fonts> FontHolder;

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename) {
	std::unique_ptr<Resource> resource(new Resource());
	
	if (!resource.get()->loadFromFile(filename)) {
		std::cout << "Nisam uspio ucitati: " << filename << std::endl;
		// throw std::runtime_error ....	
	}

	std::cout << "Uspio sam ucitati " << filename << std::endl;

	auto inserted = m_resourceMap.insert(std::make_pair(id, std::move(resource)));
	// assert ako nije ubacen, zapisano u second
}

template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) {
	auto found = m_resourceMap.find(id);
	// assert ako nije našao

	return *(found->second);
}

template<typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const {
	auto found = m_resourceMap.find(id);
	// assert ako nije našao

	return *(found->second->get());
}
