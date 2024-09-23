#include "Game.h"

// Constructor: Sets up the window, bullet manager, player, and background.
Game::Game() :
    window(sf::VideoMode(ScreenHeight, ScreenWidth), "TinySpaceInvaders",
        sf::Style::Close | sf::Style::Titlebar), // Create a window with the given size and title.
    bulletmanager(ResourceManager::getInstance().getTexture("./Assets/Images/PlayerBullet.png"), 300.0f), // Initialize bullet manager with texture and speed.
    player(&ResourceManager::getInstance().getTexture("./Assets/Images/Player.png"), 0.1f, sf::Vector2f(PlayerStartingX, PlayerStartingY), bulletmanager) // Initialize player with texture, speed, position, and bullet manager.
    , enemymanager(&ResourceManager::getInstance().getTexture("./Assets/Images/Explosion.png"), 100.f)
{
    // Set the texture for the background and scale it to fit the window.
    SpaceBackground.setTexture(ResourceManager::getInstance().getTexture("./Assets/Images/Background.png"));
    SpaceBackground.scale(3.375f, 4.0f); // Adjust the background to cover the entire window.
}

// Main game loop: Runs the game, processing events, updating objects, and rendering.
void Game::run()
{
    // The game loop continues as long as the window is open and the Escape key isn't pressed.
    while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {

        ProccessEvents(); // Handle input and events.

        float deltaTime = clock.restart().asSeconds(); // Calculate time elapsed between frames.

        player.HandleInput(); // Process player-specific input.
        Update(deltaTime); // Update the state of the game based on deltaTime.
        Render(); // Render all objects to the window.
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
    checkEnemyCollisions(enemymanager.getEnemies(), bulletmanager.getBullets());
    enemymanager.update(deltaTime);
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
    window.display(); // Display the current frame.
}

// Renders the space background image to the window.
void Game::RenderBackGround()
{
    window.draw(SpaceBackground); // Draw the background sprite to the window.
}

void Game::checkEnemyCollisions(std::vector<Enemy>& enemies, std::vector<Bullet>& bullets) {
    for (auto& enemy : enemies) {
        for (size_t i = 0; i < bullets.size(); ++i) {
            if (enemy.GetBounds().intersects(bullets[i].GetBounds()) && !enemy.IsDead()) {
                // Collision detected between enemy and bullet
                std::cout << "Collision detected!" << std::endl;

                // Set the enemy as dead to trigger the death animation
                enemy.SetDead(true);
                enemymanager.incrementDeathCount();

                // Remove the bullet that hit the enemy
                bullets.erase(bullets.begin() + i);
                --i; // Adjust index to avoid skipping the next bullet
                break; // Break out of bullet loop since enemy is hit
            }
        }
    }
}

