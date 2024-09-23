#include "BulletManager.h"

BulletManager::BulletManager(const sf::Texture& texture, float bulletSpeed)
    : bulletTexture(texture), bulletSpeed(bulletSpeed) {}

void BulletManager::shoot(const sf::Vector2f& position) {
    bullets.emplace_back(&bulletTexture, bulletSpeed, position);
    std::cout << "pew pew \n";
}

void BulletManager::update(float deltaTime) {
    for (size_t i = 0; i < bullets.size(); ++i) {
        bullets[i].Update(deltaTime);
        // Remove off-screen bullets within the update function
        if (bullets[i].isOffScreen()) {
            bullets.erase(bullets.begin() + i);
            --i; // Adjust index after erasing
        }
    }
}

void BulletManager::draw(sf::RenderWindow& window) {
    for (auto& bullet : bullets) {
        bullet.Draw(window);
    }
}

const std::vector<Bullet>& BulletManager::getBullets() const {
    return bullets;
}
