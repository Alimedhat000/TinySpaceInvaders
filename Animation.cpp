#include "Animation.h"

Animation::Animation(sf::Texture* Texture, sf::Vector2u ImgCount, float SwitchToNextTime)
{
    this->ImgCount = ImgCount;
    this->SwitchToNextTime = SwitchToNextTime;
    TotalAnimationTime = 0.0f;
    CurrentImg.x = 0;

    TextureRect.width = Texture->getSize().x / (float)ImgCount.x;
    TextureRect.height = Texture->getSize().y / (float)ImgCount.y;
}

Animation::~Animation()
{
}

void Animation::Update(int row, float deltaTime) {
    CurrentImg.y = row;
    TotalAnimationTime += deltaTime;

    if (TotalAnimationTime >= SwitchToNextTime) {
        TotalAnimationTime -= SwitchToNextTime;
        CurrentImg.x++;
        if (CurrentImg.x >= ImgCount.x) {
            CurrentImg.x = 0;
        }

    }

    TextureRect.left = CurrentImg.x * TextureRect.width;
    TextureRect.top = CurrentImg.y * TextureRect.height;

}
