#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
class Text
{
public:
    Text(sf::Texture* texture);

    void draw_Text(sf::Vector2f Position, const std::string String, const float Scale, sf::RenderWindow& window);
private:

    unsigned char CharHeight;
    unsigned char CharWidth;
    sf::Sprite Character;
};

