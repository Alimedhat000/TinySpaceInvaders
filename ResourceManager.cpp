#include "ResourceManager.h"
#include <stdexcept>

// Singleton instance of ResourceManager
ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

// Load or retrieve a texture by file path
sf::Texture& ResourceManager::getTexture(const std::string& filePath) {
    // Check if the texture is already loaded
    if (textures.find(filePath) == textures.end()) {
        // If not loaded, load the texture and store it in the map
        sf::Texture texture;
        if (!texture.loadFromFile(filePath)) {
            throw std::runtime_error("Failed to load texture: " + filePath);
        }
        textures[filePath] = texture; // Store in the map
    }

    // Return the texture (we return by reference)
    return textures[filePath];
}
