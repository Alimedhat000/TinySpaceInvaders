#include "EnemyManager.h"

EnemyManager::EnemyManager(sf::Texture* texture, float speed)
    : enemySpeed(speed), DeathTexture(texture), NumberOfDeaths(0)
    , sound()
{
    std::map<unsigned char, std::string> texturePaths = {
        {0, ENEMY_0_FILEPATH},
        {1, ENEMY_1_FILEPATH},
        {2, ENEMY_2_FILEPATH}
    };


    // Load all textures from provided paths
    for (const auto& pair : texturePaths) { // Use pair to avoid structured bindings
        unsigned char type = pair.first;      // Get the type
        const std::string& Curpath = pair.second; // Get the path

        sf::Texture texture; // Create a local texture object
        if (texture.loadFromFile(Curpath)) {
            enemyTextures[type] = std::move(texture); // Move texture into the map
        }
    }
    GenerateEnemies(6, 10, 2);
    //spawnEnemy(sf::Vector2f(100.f, 100.f), 0);

}

void EnemyManager::GenerateEnemies(int rows, int cols, int rowsPerType) {
    unsigned char type = 0;
    for (int row = 0; row < rows; ++row) { // Loop through rows
        for (int col = 0; col < cols; ++col) { // Loop through columns
            // Calculate position based on grid
            sf::Vector2f position(50.f + col * 100.f, 75.f + row * 50.f); // Offset each type vertically
            spawnEnemy(position, type); // Spawn the enemy
        }
        if (row % 2) {
            type++;
            if (type > 2) {
                type = 0;
            }
        }
    }

}

void EnemyManager::spawnEnemy(sf::Vector2f position, unsigned char type) {

    enemies.emplace_back(&enemyTextures[type], DeathTexture, enemySpeed, position, type); // Spawn a new enemy
}

void EnemyManager::update(float deltaTime) {
    for (auto& enemy : enemies) {

        enemy.Update(deltaTime); // Update each enemy's state
        enemy.SetSpeed(enemySpeed);
    }
    sound.SetEnemyMoveSoundSpeed(NumberOfDeaths);
    sound.PlayEnemyMoveSound();

}

void EnemyManager::draw(sf::RenderWindow& window) {
    for (auto& enemy : enemies) {
        enemy.Draw(window); // Draw each enemy
    }
}

bool EnemyManager::checkEnemiesReachBottom() const {
    for (const auto& enemy : enemies) {
        if (enemy.GetPosition().y >= ScreenHeight) {
            return true; // An enemy has reached the bottom
        }
    }
    return false;
}

std::vector<Enemy>& EnemyManager::getEnemies() {
    return enemies;
}


void EnemyManager::incrementDeathCount() {
    NumberOfDeaths++;
    // Optionally, you can also adjust the speed here
    adjustSpeed();
}

void EnemyManager::adjustSpeed() {
    // For example, increase speed by a factor based on the number of deaths
    enemySpeed = BASE_SPEED + (NumberOfDeaths * SPEED_INCREMENT); // BASE_SPEED and SPEED_INCREMENT are defined constants
}
