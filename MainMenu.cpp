#include "MainMenu.h"

MainMenu::MainMenu()
{
    Background.setTexture(ResourceManager::getInstance().getTexture("./Assets/Images/BG.png"));
    StartButton.setTexture(ResourceManager::getInstance().getTexture("./Assets/Images/Start_BTN.png"));
    Title.setTexture(ResourceManager::getInstance().getTexture("./Assets/Images/Title.png"));


    // Set the positions of the sprites so they are visible
    Background.setPosition(0.f, 0.f); // Position background at the top-left corner
    Title.setPosition(ScreenHeight / 2 - Title.getGlobalBounds().width / 2, 100.f);  // Adjust position to be in the center or top
    StartButton.setPosition(ScreenHeight / 2 - StartButton.getGlobalBounds().width / 2, 400.f);  // Position the Start Button

}

bool MainMenu::HandleInput(sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::IntRect StartButtonRect(StartButton.getPosition().x
            , StartButton.getPosition().y
            , StartButton.getGlobalBounds().width
            , StartButton.getGlobalBounds().height
        );
        if (StartButtonRect.contains(sf::Mouse::getPosition(window)))
        {
            //std::this_thread::sleep_for(std::chrono::seconds(1));
            return true;
        }
    }
    return false;

}

void MainMenu::Update(sf::RenderWindow& window)
{
    sf::IntRect StartButtonRect(StartButton.getPosition().x
        , StartButton.getPosition().y
        , StartButton.getGlobalBounds().width
        , StartButton.getGlobalBounds().height
    );
    if (StartButtonRect.contains(sf::Mouse::getPosition(window)))
    {
        StartButton.setTexture((ResourceManager::getInstance().getTexture("./Assets/Images/Start_BTN_hover.png")));
    }
    else {
        StartButton.setTexture(ResourceManager::getInstance().getTexture("./Assets/Images/Start_BTN.png"));
    }
}

void MainMenu::Draw(sf::RenderWindow& window)
{
    window.draw(Background);
    window.draw(Title);
    window.draw(StartButton);
}
