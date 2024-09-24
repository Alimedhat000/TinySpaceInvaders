#pragma once
#include "BulletManager.h"
#include "Enemy.h"
#include "Sound.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>

class EnemyManager {
public:
    // Constructor to load the texture and initialize speed
    EnemyManager(sf::Texture* texture, float speed);

    void GenerateEnemies(int Rows, int Cols, int RowsPerType);

    // Spawns a new enemy at a specific position with a given type
    void spawnEnemy(sf::Vector2f position, unsigned char type);

    // Updates all enemies
    void update(float deltaTime);

    // Draws all enemies on the screen
    void draw(sf::RenderWindow& window);

    // Check if any enemy reaches the bottom of the screen
    bool checkEnemiesReachBottom() const;

    std::vector<Enemy>& getEnemies();

    void incrementDeathCount();

    void adjustSpeed();




private:

    const float BASE_SPEED = 100.0f; // Initial speed of enemies
    const float SPEED_INCREMENT = 75.0f; // Speed increment per death

    Sound sound;
    sf::Texture* DeathTexture;
    std::vector<Enemy> enemies; // Stores all active enemies
    float enemySpeed; // Base speed for enemies
    std::map<unsigned char, sf::Texture> enemyTextures; // Textures for the enemies
    int NumberOfDeaths;
};
