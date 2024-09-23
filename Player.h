#pragma once
#include "Animation.h"
#include "SFML/Graphics.hpp"
#include "Global.h"
#include "BulletManager.h"
#include <vector>

class Player
{
public:
    Player(sf::Texture* texture, float speed, sf::Vector2f Position, BulletManager& bulletmanager);
    void HandleInput();
    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);
    void SetPosition(sf::Vector2f Position);
    sf::Vector2f GetPosition()const;
    sf::FloatRect GetBounds()const;

    void shoot(BulletManager& bulletmanager);

private:
    Animation animation;
    sf::Texture* playerTexture;
    float speed;
    sf::RectangleShape playerShape;

    BulletManager& bulletmanager;
    float ShootCoolDown;
    float ShootCoolDownMax;

};

