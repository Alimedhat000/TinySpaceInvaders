#include "Player.h"

// Constructor: Initializes the player with texture, speed, initial position, and a reference to the bullet manager.
Player::Player(sf::Texture* texture, float speed, sf::Vector2f Position, BulletManager& bulletmanager)
    : playerTexture(texture), speed(speed), bulletmanager(bulletmanager),
    animation(texture, sf::Vector2u(5, 1), SwitchToNextTime) // Initialize animation with texture and image count.
    , sound()
{
    // Set the size of the player, origin point, texture, and initial position.
    playerShape.setSize(sf::Vector2f(GlobalSize, GlobalSize)); // Set player's width and height.
    playerShape.setOrigin(playerShape.getSize() / 2.0f); // Set origin to the center of the player.
    playerShape.setTexture(playerTexture); // Apply texture to the player shape.
    playerShape.setPosition(Position); // Set player's initial position on the screen.

    ShootCoolDown = 0.0f; // Initialize cooldown for shooting.
    ShootCoolDownMax = 0.2f; // Maximum time between two consecutive shots.
}

// Handles input for player movement and shooting.
void Player::HandleInput()
{
    // Move player left when 'A' key is pressed.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && playerShape.getPosition().x > GlobalSize) {
        playerShape.move(-speed, 0.0f); // Move left
    }
    // Move player right when 'D' key is pressed.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && playerShape.getPosition().x < ScreenHeight - GlobalSize) {
        playerShape.move(speed, 0.0f); // Move right
    }
    // Shoot a bullet when the space bar is pressed and cooldown allows.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && ShootCoolDown <= 0.0f) {
        shoot(bulletmanager); // Fire a bullet
        ShootCoolDown = ShootCoolDownMax; // Reset cooldown after shooting.
    }
}

// Updates the player's state (e.g., shooting cooldown, animation).
void Player::Update(float deltaTime)
{
    // Decrease the cooldown timer as time progresses.
    if (ShootCoolDown > 0.f) {
        ShootCoolDown -= deltaTime; // Decrease cooldown
    }

    // Update player animation (0 is the row for player animations in the sprite sheet).
    animation.Update(0, deltaTime);
    playerShape.setTextureRect(animation.TextureRect); // Apply current animation frame to the player sprite.
}

// Draws the player to the game window.
void Player::Draw(sf::RenderWindow& window)
{
    window.draw(playerShape); // Draw the player on the screen.
}

// Sets the player's position to a specific point on the screen.
void Player::SetPosition(sf::Vector2f Position)
{
    playerShape.setPosition(Position);
}

// Gets the player's current position on the screen.
sf::Vector2f Player::GetPosition() const
{
    return playerShape.getPosition();
}

// Returns the player's bounding box for collision detection.
sf::FloatRect Player::GetBounds() const
{
    return playerShape.getGlobalBounds(); // Returns the rectangular bounds of the player.
}

// Shoots a bullet from the player's current position.
void Player::shoot(BulletManager& bulletmanager)
{
    // Calculate bullet position based on player position, adjusting for centering.
    sf::Vector2f bulletPosition = playerShape.getPosition();
    bulletPosition.x -= 40.f / 2 - 9.0f; // Center the bullet's X position relative to the player (The 9.0f is an offset to better center the Bullet). 
    bulletPosition.y -= 40.f / 2; // Center the bullet's Y position relative to the player.

    //Play Shooting SoundEffect
    sound.PlayShootSound();

    // Pass the bullet position to the BulletManager for firing.
    bulletmanager.shoot(bulletPosition);
}
