#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "BulletManager.h"
#include "ResourceManager.h"
#include <vector>
#include <iostream>

class Game
{
public:
    Game();
    void run(); // Main loop


private:
    void ProccessEvents();
    void Update(float deltaTime);
    void Render();
    void RenderBackGround();

    sf::RenderWindow window;
    Player player;
    BulletManager bulletmanager;
    sf::Clock clock;

    sf::Sprite SpaceBackground;

};

