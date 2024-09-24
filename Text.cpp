#include "Text.h"

Text::Text(sf::Texture* texture) :

    CharHeight(texture->getSize().y),
    CharWidth(texture->getSize().x / 96)

{
    Character.setTexture(*texture);
}

void Text::draw_Text(sf::Vector2f Position, const std::string String, const float Scale, sf::RenderWindow& window)
{
    sf::Vector2f CharacterPosition = Position;

    for (std::string::const_iterator c = String.begin(); c != String.end(); c++)
    {
        if (*c == '\n')
        {
            CharacterPosition.x = Position.x;
            CharacterPosition.y += CharHeight;
            continue;
        }
        Character.setPosition(CharacterPosition);
        Character.setTextureRect(sf::IntRect(CharWidth * (*c - 32), 0, CharWidth, CharHeight));
        Character.setScale(Scale, Scale);
        CharacterPosition.x += CharWidth * Scale;
        window.draw(Character);
    }
}

