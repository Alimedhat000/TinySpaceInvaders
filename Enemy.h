#pragma once
#include "Animation.h"
#include "Global.h"
#include "ResourceManager.h"
#include <SFML/Graphics.hpp>


// The Enemy Class represents the Enemy SpaceInvaders
// It handles movement, and updating state and Animation.
class Enemy
{
public:
    // Constructor: Initializes the Enemy with a texture, speed, initial position, and it's type.
    Enemy(sf::Texture* texture, sf::Texture* deathTexture, float speed, sf::Vector2f Position, unsigned char Type);

    // Updates the Enemy's state, including Position and Animation, based on DeltaTime 
    void Update(float deltaTime);

    // Draws the Enemy sprite on the given window.
    void Draw(sf::RenderWindow& window);

    // Sets the position of the Enemy on the screen.
    void SetPosition(sf::Vector2f Position);

    // Returns the Type of the Enemy.
    unsigned char GetType()const;

    // Returns the current position of the Enemy.
    sf::Vector2f GetPosition()const;

    // Returns the bounding box of the Enemy for collision detection.
    sf::FloatRect GetBounds()const;

    bool IsDead() const;

    void SetDead(bool newDead);

    void SetDeathAnimation();

    void SetSpeed(float NewSpeed);

private:
    // Handles animation frames for the Enemy sprite.
    Animation animation;

    Animation DeathAnimation;

    // The Enemy's texture used to display the sprite.
    sf::Texture* EnemyTexture;

    sf::Vector2f StartingPosition;


    sf::Texture* DeathTexture;
    // Current Moving Direction of the Enemy (-1 - Left, 0 - Down, 1 - Right)
    char Direction;

    bool Dead;

    // The Type of the enemy
    unsigned char Type;

    // Speed at which the Enemy moves.
    float speed;

    float hitBoxScale{ 0.3f };

    // Rectangle shape used to represent the Enemy.
    sf::RectangleShape EnemyShape;

    // Time control for firing bullets.
    unsigned int  MoveCoolDown;
    unsigned int MoveCoolDownMax; // Maximum cooldown time between shots.

};

