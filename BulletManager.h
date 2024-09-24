#pragma once

#include "Bullet.h"
#include <vector>
#include <iostream>

// The BulletManager class manages multiple bullets, handling their creation, updating, 
// rendering, and removing when they go off-screen.
class BulletManager {
public:
    // Constructor: Initializes the manager with a texture and bullet speed.
    BulletManager(const sf::Texture& texture, float bulletSpeed, bool Direction);

    // Shoots a new bullet from the given position.
    void shoot(const sf::Vector2f& position);

    // Updates the position of all bullets and removes any that go off-screen.
    void update(float deltaTime);

    // Draws all active bullets to the window.
    void draw(sf::RenderWindow& window);

    // Returns a constant reference to the current list of bullets.
    std::vector<Bullet>& getBullets(); // Non-const reference


private:
    // List of active bullets being managed.
    std::vector<Bullet> bullets;

    // Texture used for each bullet.
    sf::Texture bulletTexture;

    // Speed at which bullets move.
    float bulletSpeed;

    bool Direction;
};
