#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"

int main() {
    int Height = 1024;
    int Width = 720;
    float playerHeight = 80.f;
    float playerWidth = 80.f;

    sf::RenderWindow window(

        sf::VideoMode(Height, Width), "SFML works!",
        sf::Style::Close | sf::Style::Titlebar /*| sf::Style::Resize*/);

    sf::RectangleShape player(sf::Vector2f(playerHeight, playerWidth));
    player.setOrigin(playerHeight / 2, playerWidth / 2);

    sf::Texture SpaceInvaderTexture;
    SpaceInvaderTexture.loadFromFile("./Assets/Images/Player.png");
    player.setTexture(&SpaceInvaderTexture);


    Animation animation(&SpaceInvaderTexture, sf::Vector2u(5, 1), 0.5f);

    float deltaTime = 0.0f;
    sf::Clock clock;


    while (window.isOpen()) {

        deltaTime = clock.restart().asSeconds();


        sf::Event myEvent;
        while (window.pollEvent(myEvent)) {
            switch (myEvent.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::Resized:
                std::cout << "height: " << myEvent.size.height
                    << " Width: " << myEvent.size.width << "\n";
                break;

            case sf::Event::TextEntered:
                if (myEvent.text.unicode < 128) {
                    std::cout << (char)myEvent.text.unicode;
                }
                break;

            default:
                break;
            }
        }



        animation.Update(0, deltaTime);
        player.setTextureRect(animation.TextureRect);



        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            player.move(-0.1f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            player.move(0.0f, -0.1f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            player.move(0.0f, 0.1f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            player.move(0.1f, 0.0f);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            player.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        }
        window.clear();
        window.draw(player);
        window.display();
    }

    return 0;
}
