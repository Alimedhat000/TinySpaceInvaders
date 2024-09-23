#pragma once

#include "Bullet.h"
#include <vector>
#include <iostream>

class BulletManager {
public:
    BulletManager(const sf::Texture& texture, float bulletSpeed);

    void shoot(const sf::Vector2f& position); // Create a new bullet
    void update(float deltaTime); // Update all bullets
    void draw(sf::RenderWindow& window); // Draw all bullets

    const std::vector<Bullet>& getBullets() const; // Get current bullets

private:
    std::vector<Bullet> bullets; // List of bullets
    sf::Texture bulletTexture; // Bullet texture
    float bulletSpeed; // Speed of the bullets
};
