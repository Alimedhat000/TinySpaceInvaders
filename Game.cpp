#include "Game.h"

Game::Game() :
    window(sf::VideoMode(ScreenHeight, ScreenWidth), "TinySpaceInvaders",
        sf::Style::Close | sf::Style::Titlebar)
    , bulletmanager(ResourceManager::getInstance().getTexture("./Assets/Images/PlayerBullet.png"), 300.0f),
    player(&ResourceManager::getInstance().getTexture("./Assets/Images/Player.png"), 0.1f, sf::Vector2f(PlayerStartingX, PlayerStartingY), bulletmanager)
{
    SpaceBackground.setTexture(ResourceManager::getInstance().getTexture("./Assets/Images/Background.png"));
    SpaceBackground.scale(3.375f, 4.0f);

}

void Game::run()
{

    while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {

        ProccessEvents();
        float deltaTime = clock.restart().asSeconds();
        player.HandleInput();
        Update(deltaTime);
        Render();
    }
}

void Game::ProccessEvents()
{
    sf::Event myEvent;
    while (window.pollEvent(myEvent)) {
        switch (myEvent.type) {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

void Game::Update(float deltaTime)
{
    bulletmanager.update(deltaTime);
    player.Update(deltaTime);

}

void Game::Render()
{
    window.clear();
    RenderBackGround();
    bulletmanager.draw(window);
    player.Draw(window);
    window.display();
}

void Game::RenderBackGround()
{
    window.draw(SpaceBackground);
}
