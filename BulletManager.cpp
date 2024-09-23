#include "BulletManager.h"

// Constructor: Sets the bullet texture and speed for the manager.
BulletManager::BulletManager(const sf::Texture& texture, float bulletSpeed)
    : bulletTexture(texture), bulletSpeed(bulletSpeed) {}

// Creates a new bullet at the given position and adds it to the bullets list.
void BulletManager::shoot(const sf::Vector2f& position) {
    bullets.emplace_back(&bulletTexture, bulletSpeed, position); // Create a new bullet and push it to bullets vector.
    //std::cout << "Pew Pew!\n"; // Debug message for shooting.
}

// Updates all bullets, moves them based on deltaTime, and removes bullets that are off-screen.
void BulletManager::update(float deltaTime) {
    for (size_t i = 0; i < bullets.size(); ++i) {
        bullets[i].Update(deltaTime); // Update the bullet's position.
        // Check if the bullet has moved off the screen.
        if (bullets[i].isOffScreen()) {
            bullets.erase(bullets.begin() + i); // Remove off-screen bullet.
            --i; // Adjust index after removal to avoid skipping elements.
        }
    }
}

// Draws all bullets in the bullets list to the provided window.
void BulletManager::draw(sf::RenderWindow& window) {
    for (auto& bullet : bullets) {
        bullet.Draw(window); // Render each bullet.
    }
}

// Returns a constant reference to the vector containing all bullets.
std::vector<Bullet>& BulletManager::getBullets() {
    return bullets;
}
