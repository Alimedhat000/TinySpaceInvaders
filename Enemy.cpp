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

    Dead = false;
    MoveCoolDown = 0.0; // Initialize cooldown for shooting.
    MoveCoolDownMax = 100; // Maximum time between two consecutive shots.

    shootCoolDown = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.0)); // Initialize as a Random Number to make the cooldown Different for each enemy fix enemies firing in patches
    MaxShootCoolDown = 2.f;

    AmILoaded = false;
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

    // Update Enemy animation.
    animation.Update(0, deltaTime);
    EnemyShape.setTextureRect(animation.TextureRect);
}

void Enemy::Draw(sf::RenderWindow& window) {
    if (!IsDead() || (IsDead() && EnemyShape.getSize().x > 0)) {
        window.draw(EnemyShape); // Only draw if the enemy isn't dead or if it's still visible
        AmILoaded = true;
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
    // Get the original bounds of the enemy shape
    sf::FloatRect originalBounds = EnemyShape.getGlobalBounds();

    // Create a smaller bounding box based on the scaling factor
    return sf::FloatRect(
        originalBounds.left + (originalBounds.width * (1 - hitBoxScale)) / 2,
        originalBounds.top + (originalBounds.height * (1 - hitBoxScale)) / 2,
        originalBounds.width * hitBoxScale,
        originalBounds.height * hitBoxScale
    );
}

bool Enemy::IsDead() const
{
    return Dead;
}

void Enemy::SetDead(bool newDead)
{
    Dead = newDead;
    Deadtime = clock.getElapsedTime();

}

sf::Int32 Enemy::getDeadTime()const
{
    return Deadtime.asMilliseconds();
}

void Enemy::SetDeathAnimation()
{
    EnemyShape.setTexture(DeathTexture);
}

bool Enemy::ShouldShoot(const sf::Vector2f& playerPosition, int level)
{
    float distance = std::sqrt(std::pow(EnemyShape.getPosition().x - playerPosition.x, 2) +
        std::pow(EnemyShape.getPosition().y - playerPosition.y, 2));

    // Base shooting probability, increase it based on the level
    float shootProbability = 2.5f + (level * 0.5f); // Increase base probability as level increases

    // Increase probability if close to the player
    if (distance < 200.0f) { // Change this value to set the proximity threshold
        shootProbability += (1.0f - (distance / 200.0f)) * 50.0f; // Increase probability as distance decreases
    }

    // Cap shootProbability based on level (optional, adjust as needed)
    if (shootProbability > 80.0f) {
        shootProbability = 80.0f; // Limit maximum probability to 80%
    }

    // Random chance to shoot based on calculated probability
    return rand() % 100 < shootProbability;
}


void Enemy::SetSpeed(float NewSpeed) {
    speed = NewSpeed;
}

float Enemy::GetShootCoolDown()const
{
    return shootCoolDown;
}

void Enemy::SetShootCoolDown(float Value, int level)
{
    // Reduce the cooldown based on the level
    float coolDownReduction = 0.05f * level; // Adjust this factor to control the reduction rate
    float minCoolDown = 0.5f; // Set a minimum cooldown value to avoid too fast shooting

    // Calculate the new cooldown
    shootCoolDown = Value - coolDownReduction;

    // Ensure the cooldown doesn't go below the minimum threshold
    if (shootCoolDown < minCoolDown) {
        shootCoolDown = minCoolDown;
    }
}

float Enemy::GetMaxShootCoolDown()const
{
    return MaxShootCoolDown;
}

bool Enemy::GetAmILoaded() const
{
    return AmILoaded;
}
