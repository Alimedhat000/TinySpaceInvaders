#include "Animation.h"

// Constructor: Initializes the image count, switch time, and calculates the width and height of each frame.
Animation::Animation(sf::Texture* Texture, sf::Vector2u ImgCount, float SwitchToNextTime)
{
    this->ImgCount = ImgCount; // Store the number of frames in the sprite sheet.
    this->SwitchToNextTime = SwitchToNextTime; // Set the interval for switching frames.
    TotalAnimationTime = 0.0f; // Initialize the time passed since the last switch.
    CurrentImg.x = 0; // Start from the first frame (column).

    // Calculate the width and height of each frame in the sprite sheet.
    TextureRect.width = Texture->getSize().x / (float)ImgCount.x;
    TextureRect.height = Texture->getSize().y / (float)ImgCount.y;
}

// Updates the current frame of animation based on elapsed time (deltaTime) and the row to display.
void Animation::Update(int row, float deltaTime) {
    CurrentImg.y = row; // Set the current row of the animation (usually based on the character's action).
    TotalAnimationTime += deltaTime; // Increment the total time passed by the delta time.

    // Check if it's time to switch to the next frame.
    if (TotalAnimationTime >= SwitchToNextTime) {
        TotalAnimationTime -= SwitchToNextTime; // Reset the time for the next frame.
        CurrentImg.x++; // Move to the next column (frame).

        // If we reached the end of the frames in the row, loop back to the first frame.
        if (CurrentImg.x >= ImgCount.x) {
            CurrentImg.x = 0; // Loop back to the start.
        }
    }

    // Update the texture rectangle to display the correct portion of the sprite sheet.
    TextureRect.left = CurrentImg.x * TextureRect.width;
    TextureRect.top = CurrentImg.y * TextureRect.height;
}
