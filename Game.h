#pragma once

#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Sound.h"
#include "Text.h"
#include "StateMachine.h"
#include "MainMenu.h"
#include "Player.h"
#include "BulletManager.h"
#include "ResourceManager.h"
#include "EnemyManager.h"
#include <vector>
#include <iostream>



// The Game class represents the main game loop and handles core operations like input processing,
// game updates, rendering, and resource management.
class Game
{
public:
    // Constructor: Initializes the game window, player, bullet manager, and background.
    Game();

    // Main game loop: processes events, updates game state, and renders the game.
    void run();

    void checkEnemyCollisions(std::vector<Enemy>& enemies, std::vector<Bullet>& bullets);

    void CheckPlayerCollision(std::vector<Bullet>& Bullets);
private:
    // Handles user input and window events.
    void ProccessEvents();

    // Updates the game objects (player, bullets) based on deltaTime.
    void Update(float deltaTime);

    // Renders all game objects to the screen.
    void Render();

    // Renders the background image.
    void RenderBackGround();

    void RenderScore();

    void RenderLiveCounter();

    void RenderLevelCounter();

    void showMainMenu();

    void showDeathScreen();

    // The main window where the game is displayed.
    sf::RenderWindow window;

    //Menu menu;
    MainMenu mainMenu;

    StateMachine stateMachine;

    // The player object, which can move and shoot bullets.
    Player player;

    // Manages all bullets shot by the player.
    BulletManager bulletmanager;

    // Manages all the enemies
    EnemyManager enemymanager;

    //Manages and Plays all The sounds
    Sound sound;

    Text text;
    // Tracks time between frames to ensure smooth movement and animation.
    sf::Clock clock;

    // Sprite used to display the background image.
    sf::Sprite SpaceBackground;

    int Scores{ 0 };
};
