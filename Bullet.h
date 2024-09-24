#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

// The Bullet class represents a bullet object, handling its movement, rendering,
// and checking if it has gone off-screen.
class Bullet
{
public:
    // Constructor: Initializes the bullet with a texture, speed, and starting position.
    Bullet(sf::Texture* texture, float speed, sf::Vector2f Position, bool Direction);

    // Updates the position of the bullet based on the time elapsed.
    void Update(float deltaTime);

    // Renders the bullet sprite to the provided window.
    void Draw(sf::RenderWindow& window);

    // Checks if the bullet has moved off the top of the screen.
    bool isOffScreen() const;

    // Returns the bounding box of the bullet's sprite for collision detection.
    sf::FloatRect GetBounds() const;

private:
    // The sprite that visually represents the bullet.
    sf::Sprite BulletSprite;

    // The speed at which the bullet travels (negative direction along the Y-axis).
    float speed;

    bool Direction;
};
