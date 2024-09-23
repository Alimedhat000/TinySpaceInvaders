#include "Enemy.h"


Enemy::Enemy(sf::Texture* texture, sf::Texture* deathTexture, float speed, sf::Vector2f Position, unsigned char Type)
    : EnemyTexture(texture), speed(speed), Type(Type), StartingPosition(Position), DeathTexture(deathTexture),
    animation(texture, sf::Vector2u(2, 1), SwitchToNextTime * 2.f),
    DeathAnimation(deathTexture, sf::Vector2u(15, 1), 0.1f * SwitchToNextTime)
{
    // Set the size of the Enemy, origin point, texture, and initial position.
    EnemyShape.setSize(sf::Vector2f(GlobalSize * 1.2f, GlobalSize * 1.2f));
    EnemyShape.setOrigin(EnemyShape.getSize() / 2.0f);
    EnemyShape.setPosition(Position);
    EnemyShape.setTexture(EnemyTexture);

    // Initialize Direction to Right 
    Direction = 1;

    Dead = false;

    MoveCoolDown = 0.0; // Initialize cooldown for shooting.
    MoveCoolDownMax = 100; // Maximum time between two consecutive shots.
}

void Enemy::Update(float deltaTime)
{
    if (IsDead()) {
        SetDeathAnimation();
        // Update the death animation
        DeathAnimation.Update(0, deltaTime);

        // Check if the death animation has completed
        if (DeathAnimation.CurrentImg.x == 0 && DeathAnimation.TotalAnimationTime < deltaTime) {
            // Remove or hide the enemy here
            EnemyShape.setSize(sf::Vector2f(0, 0)); // Example: Hide the enemy
            return; // Exit the update as the enemy is dead
        }

        // Set the texture rectangle for the explosion/death animation
        EnemyShape.setTextureRect(DeathAnimation.TextureRect);
        return;
    }

    // Decrease the cooldown timer as time progresses.
    if (MoveCoolDown > 0.f) {
        MoveCoolDown -= deltaTime; // Decrease cooldown
    }
    if (MoveCoolDown <= 0.0f)
    {
        // Move the enemy in the current direction
        if (Direction == 1) // Move Right
            EnemyShape.move(speed * deltaTime, 0);
        else if (Direction == -1) // Move Left
            EnemyShape.move(-speed * deltaTime, 0);

        // Check for boundary conditions to switch direction and move down
        if (EnemyShape.getPosition().x <= StartingPosition.x - 1) {
            Direction = 1; // Change direction to right
            EnemyShape.move(0, 10000 * deltaTime); // Move down
        }
        else if (EnemyShape.getPosition().x >= StartingPosition.x + 25) {
            Direction = -1; // Change direction to left
            EnemyShape.move(0, 10000 * deltaTime); // Move down
        }
        MoveCoolDown = MoveCoolDownMax;
    }
    // Update Enemy animation.
    animation.Update(0, deltaTime);
    EnemyShape.setTextureRect(animation.TextureRect);
}

void Enemy::Draw(sf::RenderWindow& window) {
    if (!IsDead() || (IsDead() && EnemyShape.getSize().x > 0)) {
        window.draw(EnemyShape); // Only draw if the enemy isn't dead or if it's still visible
    }
}


void Enemy::SetPosition(sf::Vector2f Position)
{
    EnemyShape.setPosition(Position);
}

unsigned char Enemy::GetType() const
{
    return Type;
}

sf::Vector2f Enemy::GetPosition() const
{
    return EnemyShape.getPosition();
}

sf::FloatRect Enemy::GetBounds() const
{
    return EnemyShape.getGlobalBounds();
}

bool Enemy::IsDead() const
{
    return Dead;
}

void Enemy::SetDead(bool newDead)
{
    Dead = newDead;
}

void Enemy::SetDeathAnimation()
{
    EnemyShape.setTexture(DeathTexture);
}

void Enemy::SetSpeed(float NewSpeed) {
    speed = NewSpeed;
}


