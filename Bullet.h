#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
class Bullet
{

public:
    Bullet(sf::Texture* texture, float speed, sf::Vector2f Position);

    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);
    bool isOffScreen()const;
    sf::FloatRect GetBounds()const;

private:
    sf::Sprite BulletSprite;
    float speed;

};

