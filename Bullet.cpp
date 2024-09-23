#include "Bullet.h"

// Constructor: Initializes the bullet's speed, sets the texture, and places the bullet at the given position.
Bullet::Bullet(sf::Texture* texture, float speed, sf::Vector2f Position)
{
    this->speed = speed; // Set the speed of the bullet.
    BulletSprite.setTexture(*texture); // Set the texture for the bullet's sprite.
    BulletSprite.setPosition(Position); // Set the initial position of the bullet.
    BulletSprite.scale(1.5f, 1.5f); // Scale the bullet sprite to make it larger.
}

// Updates the bullet's position based on the elapsed time (deltaTime) and its speed.
void Bullet::Update(float deltaTime)
{
    // Move the bullet upwards by modifying its Y position.
    BulletSprite.move(0.f, deltaTime * -speed); // Negative speed moves the bullet up the screen.
}

// Draws the bullet sprite onto the given window.
void Bullet::Draw(sf::RenderWindow& window)
{
    window.draw(BulletSprite); // Render the bullet sprite.
}

// Returns true if the bullet has moved off the top of the screen.
bool Bullet::isOffScreen() const
{
    return BulletSprite.getPosition().y < 0; // Bullet is off-screen if its Y position is less than 0.
}

// Returns the bounding rectangle of the bullet sprite, useful for collision detection.
sf::FloatRect Bullet::GetBounds() const
{
    return BulletSprite.getGlobalBounds(); // Return the global bounds (bounding box) of the bullet sprite.
}
