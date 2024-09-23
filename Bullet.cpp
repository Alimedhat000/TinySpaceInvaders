#include "Bullet.h"

Bullet::Bullet(sf::Texture* texture, float speed, sf::Vector2f Position)
{
    this->speed = speed;
    BulletSprite.setTexture(*texture);
    BulletSprite.setPosition(Position);
    BulletSprite.scale(1.5f, 1.5f);
}

void Bullet::Update(float deltaTime)
{
    BulletSprite.move(0.f, deltaTime * -speed);
}

void Bullet::Draw(sf::RenderWindow& window)
{
    window.draw(BulletSprite);
}

bool Bullet::isOffScreen() const
{
    return BulletSprite.getPosition().y < 0;
}

sf::FloatRect Bullet::GetBounds() const
{
    return BulletSprite.getGlobalBounds();
}
