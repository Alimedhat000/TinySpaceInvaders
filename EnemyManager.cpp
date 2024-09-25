#include "EnemyManager.h"

EnemyManager::EnemyManager(sf::Texture* texture, float speed)
    : enemySpeed(speed), DeathTexture(texture), NumberOfDeaths(0)
    , sound(), Direction(1),
    EnemyBullet(ResourceManager::getInstance().getTexture(ENEMY_BULLET_FILEPATH), 300.0f, DIRECTION_DOWN)
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
    FinishedLoading = false;
    GenerateEnemies(6, 15, 2);
    //spawnEnemy(sf::Vector2f(100.f, 100.f), 0);

}

void EnemyManager::GenerateEnemies(int rows, int cols, int rowsPerType) {
    unsigned char type = 2;
    for (int row = 0; row < rows; ++row) { // Loop through rows
        for (int col = 0; col < cols; ++col) { // Loop through columns
            // Calculate position based on grid
            sf::Vector2f position(50.f + col * 50.f, 75.f + row * 50.f); // Offset each type vertically
            spawnEnemy(position, type); // Spawn the enemy
        }
        if (row % 2) {
            type--;
            if (type < 0) {
                type = 2;
            }
        }
    }
    FinishedLoading = true;

}

void EnemyManager::spawnEnemy(sf::Vector2f position, unsigned char type) {

    enemies.emplace_back(&enemyTextures[type], DeathTexture, enemySpeed, position, type); // Spawn a new enemy
}

void EnemyManager::update(float deltaTime, sf::Vector2f PlayerPosition) {

    float leftEdge = ScreenHeight;
    float rightEdge = 0;
    const float enemyWidth = 40.0f; // Assuming each enemy is 50 pixels wide
    const float moveDownAmount = 10.0f; // Adjust to control how much enemies move down

    // Determine the edges of the group
    for (auto& enemy : enemies) {
        sf::Vector2f position = enemy.GetPosition();
        if (position.x < leftEdge) leftEdge = position.x;
        if (position.x > rightEdge) rightEdge = position.x;
    }
    //std::cout << leftEdge << "\n" << rightEdge << "\n";

    // Edge detection with dynamic enemy size
    if (rightEdge >= ScreenHeight - enemyWidth) { // Right edge
        Direction = -1; // Move left
        for (auto& enemy : enemies) {
            enemy.SetPosition({ enemy.GetPosition().x, enemy.GetPosition().y + moveDownAmount });
        }
    }
    else if (leftEdge <= enemyWidth) { // Left edge
        Direction = 1; // Move right
        for (auto& enemy : enemies) {
            enemy.SetPosition({ enemy.GetPosition().x, enemy.GetPosition().y + moveDownAmount });
        }
    }

    // Update each enemy's position and ShootCoolDown
    for (auto& enemy : enemies) {
        enemy.SetShootCoolDown(enemy.GetShootCoolDown() - deltaTime, CurLevel);
        if (enemy.GetShootCoolDown() <= 0) {
            if (enemy.ShouldShoot(PlayerPosition, CurLevel)) {
                EnemyBullet.shoot(enemy.GetPosition());
                sound.PlayEnemyShootSound(); // play Shooting sound
            }
            enemy.SetShootCoolDown(enemy.GetMaxShootCoolDown(), CurLevel);
        }


        enemy.Update(deltaTime);
        enemy.SetSpeed(enemySpeed);
        horizontalMovement = (Direction * (enemySpeed + CurLevel * SPEED_INCREMENT * NumberOfDeaths)) * deltaTime;
        enemy.SetPosition({ enemy.GetPosition().x + horizontalMovement, enemy.GetPosition().y });
    }


    EnemyBullet.update(deltaTime);
    // Play sound based on movement or deaths
    sound.SetEnemyMoveSoundSpeed(NumberOfDeaths);
    sound.PlayEnemyMoveSound();


    // Assuming you have an instance of sf::Clock named `clock`
    sf::Time elapsedTime = clock.getElapsedTime(); // Get the elapsed time since clock started

    // Check for dead enemies and remove them
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [&](Enemy& enemy) {
        // Check if the enemy is dead and the time since death exceeds 1000 milliseconds 
        // To ensure that death Animation is Finished
        return enemy.IsDead() && (elapsedTime.asMilliseconds() - enemy.getDeadTime()) > 500;
        }), enemies.end());
    if (NumberOfDeaths == 90)
    {
        CurLevel++;
        NumberOfDeaths = 0;
        GenerateEnemies(6, 15, 2);
    }
}



void EnemyManager::draw(sf::RenderWindow& window) {
    for (auto& enemy : enemies) {
        enemy.Draw(window); // Draw each enemy
    }
    EnemyBullet.draw(window); // Draws All the Bullets
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
    TotalNumberOfDeaths++;
    // adjusting the speed based on Number of Deaths
    adjustSpeed();
}

void EnemyManager::adjustSpeed() {
    //increase speed by a factor based on the number of deaths
    enemySpeed = BASE_SPEED + (NumberOfDeaths * SPEED_INCREMENT); // BASE_SPEED and SPEED_INCREMENT are defined constants
}

int EnemyManager::getDeathNumber() const
{
    return TotalNumberOfDeaths;
}

int EnemyManager::getCurLevel()const {
    return CurLevel;
}

bool EnemyManager::getLoadingStatus() const
{
    return FinishedLoading;
}

