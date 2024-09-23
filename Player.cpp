#include "Player.h"


Player::Player(sf::Texture* texture, float speed, sf::Vector2f Position, BulletManager& bulletmanager)
    :playerTexture(texture), speed(speed), bulletmanager(bulletmanager), animation(texture, sf::Vector2u(5, 1), SwitchToNextTime)
{

    playerShape.setSize(sf::Vector2f(GlobalSize, GlobalSize)); // Width and Height of the player
    playerShape.setOrigin(playerShape.getSize() / 2.0f);    //Origin of the player
    playerShape.setTexture(playerTexture); // Applying texture
    playerShape.setPosition(Position); // Setting initial Position

    ShootCoolDown = 0.0f;
    ShootCoolDownMax = 0.2f;
}

void Player::HandleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        playerShape.move(-speed, 0.0f); // Move left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        playerShape.move(speed, 0.0f);  // Move right
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && ShootCoolDown <= 0.0f) {
        shoot(bulletmanager);
        ShootCoolDown = ShootCoolDownMax;
    }
}

void Player::Update(float deltaTime)
{
    if (ShootCoolDown > 0.f)
    {
        ShootCoolDown -= deltaTime;

    }

    // Update player animation (row = 0 for player row in sprite sheet)
    animation.Update(0, deltaTime);
    playerShape.setTextureRect(animation.TextureRect); // Set the current frame of the animation
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(playerShape); // Draw player shape to the window
}

void Player::SetPosition(sf::Vector2f Position)
{
    playerShape.setPosition(Position);
}

sf::Vector2f Player::GetPosition() const
{
    return playerShape.getPosition();
}

sf::FloatRect Player::GetBounds() const
{
    return playerShape.getGlobalBounds();
}

void Player::shoot(BulletManager& bulletmanager)
{
    sf::Vector2f bulletPosition = playerShape.getPosition();
    bulletPosition.x -= 40.f / 2; // Center X
    bulletPosition.y -= 40.f / 2; // Center Y

    bulletmanager.shoot(bulletPosition);
}
