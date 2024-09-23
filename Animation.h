#pragma once
#include <SFML/Graphics.hpp>

// The Animation class handles updating and setting the current frame of animation 
// based on time and the number of images in a sprite sheet.
class Animation
{
public:
    // Constructor: initializes the animation with the texture, image count (columns and rows),
    // and the time interval to switch between frames.
    Animation(sf::Texture* texture, sf::Vector2u ImgCount, float SwitchToNextTime);

    // Updates the animation frame based on the row and the elapsed time since the last update.
    void Update(int row, float deltaTime);

public:
    // The portion of the texture (rectangular area) that corresponds to the current frame of animation.
    sf::IntRect TextureRect;
    // CurrentImg stores the current frame in the animation (current column and row).
    sf::Vector2u CurrentImg;

    // Total time that has passed since the last frame switch.
    float TotalAnimationTime;


private:
    // ImgCount stores the number of frames (images) in the sprite sheet.
    sf::Vector2u ImgCount;


    // The time interval after which the next frame should be displayed.
    float SwitchToNextTime;
};
