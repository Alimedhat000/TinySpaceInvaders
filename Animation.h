#pragma once
#include <SFML/Graphics.hpp>
class Animation
{
public:
    Animation(sf::Texture* texture, sf::Vector2u ImgCount, float SwitchToNextTime);
    ~Animation();

    void Update(int row, float deltaTime);




public:
    sf::IntRect TextureRect;
private:
    sf::Vector2u ImgCount;
    sf::Vector2u CurrentImg;

    float TotalAnimationTime;
    float SwitchToNextTime;
};

