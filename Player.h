#pragma once
#include "Animation.h"
#include "SFML/Graphics.hpp"
#include "Global.h"
#include "BulletManager.h"
#include <vector>

// The Player class represents the player-controlled spaceship.
// It handles movement, shooting bullets, and updating its state and animation.
class Player
{
public:
    // Constructor: Initializes the player with a texture, speed, initial position, and a reference to the BulletManager.
    Player(sf::Texture* texture, float speed, sf::Vector2f Position, BulletManager& bulletmanager);

    // Handles player input for movement and shooting.
    void HandleInput();

    // Updates the player's state, such as position and animation, based on deltaTime.
    void Update(float deltaTime);

    // Draws the player sprite on the given window.
    void Draw(sf::RenderWindow& window);

    // Sets the position of the player on the screen.
    void SetPosition(sf::Vector2f Position);

    // Returns the current position of the player.
    sf::Vector2f GetPosition() const;

    // Returns the bounding box of the player for collision detection.
    sf::FloatRect GetBounds() const;

    // Fires a bullet by calling the BulletManager.
    void shoot(BulletManager& bulletmanager);

private:
    // Handles animation frames for the player sprite.
    Animation animation;

    // The player's texture used to display the sprite.
    sf::Texture* playerTexture;

    // Speed at which the player moves.
    float speed;

    // Rectangle shape used to represent the player.
    sf::RectangleShape playerShape;

    // Reference to the BulletManager to handle bullets shot by the player.
    BulletManager& bulletmanager;

    // Time control for firing bullets.
    float ShootCoolDown;
    float ShootCoolDownMax; // Maximum cooldown time between shots.
};
