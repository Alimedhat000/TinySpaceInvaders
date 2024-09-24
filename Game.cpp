#include "Game.h"

// Constructor: Sets up the window, bullet manager, player, and background.
Game::Game() :
    window(sf::VideoMode(ScreenHeight, ScreenWidth), "TinySpaceInvaders",
        sf::Style::Close | sf::Style::Titlebar), // Create a window with the given size and title.
    bulletmanager(ResourceManager::getInstance().getTexture(PlAYER_BULLET_FILEPATH), 300.0f, DIRECTION_UP), // Initialize bullet manager with texture and speed.
    player(&ResourceManager::getInstance().getTexture(PlAYER_FILEPATH), 0.2f, sf::Vector2f(PlayerStartingX, PlayerStartingY), bulletmanager) // Initialize player with texture, speed, position, and bullet manager.
    , enemymanager(&ResourceManager::getInstance().getTexture(ENEMY_EXPLOSION_FILEPATH), 25.f),
    sound(),
    text(&ResourceManager::getInstance().getTexture(FONT_FILEPATH)),
    mainMenu()

{

    // Set the texture for the background and scale it to fit the window.
    SpaceBackground.setTexture(ResourceManager::getInstance().getTexture(BACKGROUND_FILEPATH));
    //SpaceBackground.scale(1.28f, 1.2f); // Adjust the background to cover the entire window.
    SpaceBackground.scale(3.375f, 4.0f); // Adjust the background to cover the entire window.
    sound.PlayBackgroundSound(); // Start The background Music
    //text.draw_Text(sf::Vector2f(100.f, 100.f), "Ali Rules", window);
}

// Main game loop: Runs the game, processing events, updating objects, and rendering.
void Game::run()
{
    // The game loop continues as long as the window is open and the Escape key isn't pressed.
    while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        float deltaTime = clock.restart().asSeconds(); // Calculate time elapsed between frames.

        if (player.GetPlayerLives() == 0) {
            stateMachine.SetCurState(2);
        }

        switch (stateMachine.GetCurState())
        {
        case 0:
            sound.PlayBackgroundSound();
            window.clear(); // Clear the previous frame.
            mainMenu.Draw(window);
            mainMenu.Update(window);
            window.display(); // Display the current frame.
            if (mainMenu.HandleInput(window)) {

                stateMachine.SetCurState(1);
            }
            break;
        case 1:
            sound.StopBackgroundSound();
            ProccessEvents(); // Handle input and events.
            player.HandleInput(); // Process player-specific input.
            Update(deltaTime); // Update the state of the game based on deltaTime.
            Render(); // Render all objects to the window.
            break;
        case 2:
            window.close();
            break;

        default:
            break;
        }

    }
}

// Processes SFML events, such as window close requests.
void Game::ProccessEvents()
{
    sf::Event myEvent;
    // Poll and process events in the event queue.
    while (window.pollEvent(myEvent)) {
        switch (myEvent.type) {
        case sf::Event::Closed: // If the close event is triggered, close the window.
            window.close();
            break;
        default:
            break;
        }
    }
}

// Updates all game objects, such as the player and bullets.
void Game::Update(float deltaTime)
{
    CheckPlayerCollision(enemymanager.EnemyBullet.getBullets());
    checkEnemyCollisions(enemymanager.getEnemies(), bulletmanager.getBullets());
    enemymanager.update(deltaTime, player.GetPosition());
    bulletmanager.update(deltaTime); // Update the position of all bullets.
    player.Update(deltaTime); // Update the player's position and actions.
}

// Renders the background, bullets, and player to the window.
void Game::Render()
{
    window.clear(); // Clear the previous frame.
    RenderBackGround(); // Draw the background.
    enemymanager.draw(window);
    bulletmanager.draw(window); // Draw all bullets.
    player.Draw(window); // Draw the player.
    RenderScore(); // Draw the current Score
    RenderLiveCounter(); // Draw Live counter of the player
    RenderLevelCounter();
    window.display(); // Display the current frame.
}

// Renders the space background image to the window.
void Game::RenderBackGround()
{
    window.draw(SpaceBackground); // Draw the background sprite to the window.
}

void Game::RenderScore()
{
    Scores = enemymanager.getDeathNumber() * 5;

    std::string ScoreString = "Score: ";
    ScoreString += std::to_string(Scores);

    text.draw_Text(sf::Vector2f(100.f, 10.f), ScoreString, ScoreScale, window);
}

void Game::RenderLiveCounter()
{
    int Lives = player.GetPlayerLives();

    std::string LivesString = "Lives: ";
    LivesString += std::to_string(Lives);

    text.draw_Text(sf::Vector2f(ScreenHeight - 250.f, 10.f), LivesString, ScoreScale, window);
}


void Game::RenderLevelCounter()
{
    int Level = enemymanager.getCurLevel();

    std::string LevelString = "Level: ";
    LevelString += std::to_string(Level);

    text.draw_Text(sf::Vector2f(430, 10.f), LevelString, ScoreScale, window);
}


void Game::checkEnemyCollisions(std::vector<Enemy>& enemies, std::vector<Bullet>& bullets) {
    for (auto& enemy : enemies) {
        for (size_t i = 0; i < bullets.size(); ++i) {
            if (enemy.GetBounds().intersects(bullets[i].GetBounds()) && !enemy.IsDead()) {
                // Collision detected between enemy and bullet
                //std::cout << "Collision detected!" << std::endl;

                // Set the enemy as dead to trigger the death animation
                enemy.SetDead(true);
                enemymanager.incrementDeathCount();
                sound.PlayEnemyDeathSound();

                // Remove the bullet that hit the enemy
                bullets.erase(bullets.begin() + i);
                --i; // Adjust index to avoid skipping the next bullet
                break; // Break out of bullet loop since enemy is hit
            }
        }
    }
}

void Game::CheckPlayerCollision(std::vector<Bullet>& Bullets)
{
    for (size_t i = 0; i < Bullets.size(); ++i) {
        if (player.GetBounds().intersects(Bullets[i].GetBounds())) {
            // Collision detected between enemy and bullet
            //std::cout << "Collision detected!" << std::endl;

            // Set the enemy as dead to trigger the death animation

            //std::cout << "I Think Im In Danger :)" << "\n";
            player.SetPlayerLives(player.GetPlayerLives() - 1);
            sound.PlayhitSound();

            // Remove the bullet that hit the enemy
            Bullets.erase(Bullets.begin() + i);
            --i; // Adjust index to avoid skipping the next bullet
            break; // Break out of bullet loop since enemy is hit
        }
    }
}

