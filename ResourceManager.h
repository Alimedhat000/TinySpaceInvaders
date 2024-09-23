#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class ResourceManager {
public:
    static ResourceManager& getInstance(); // Singleton pattern to ensure only one instance of ResourceManager

    // Load a texture and return a reference to it
    sf::Texture& getTexture(const std::string& filePath);

    // Optional: You can add similar methods for fonts, sounds, etc.
    // sf::Font& getFont(const std::string& filePath);
    // sf::SoundBuffer& getSoundBuffer(const std::string& filePath);

private:
    ResourceManager() {} // Private constructor for Singleton

    // Prevent copying
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    std::unordered_map<std::string, sf::Texture> textures; // Container to store textures

    // Optional: Containers for other resource types
    // std::unordered_map<std::string, sf::Font> fonts;
    // std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
};
