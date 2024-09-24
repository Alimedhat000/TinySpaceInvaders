#pragma once
#include <SFML/Graphics.hpp>
//#include <chrono>
//#include <thread>
#include "ResourceManager.h"
#include "Global.h"
#include "StateMachine.h"

class MainMenu
{
public:
    MainMenu();

    bool HandleInput(sf::RenderWindow& window);
    void Update(sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);

private:
    sf::Sprite Background;
    sf::Sprite Title;
    sf::Sprite StartButton;
};

