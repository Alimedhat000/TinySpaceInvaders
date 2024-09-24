#ifndef GLOBAL_H
#define GLOBAL_H

constexpr auto ENEMY_0_FILEPATH = "./Assets/Images/Enemy0.png";
constexpr auto ENEMY_1_FILEPATH = "./Assets/Images/Enemy1.png";
constexpr auto ENEMY_2_FILEPATH = "./Assets/Images/Enemy2.png";
constexpr auto ENEMY_EXPLOSION_FILEPATH = "./Assets/Images/Explosion.png";
constexpr auto PlAYER_FILEPATH = "./Assets/Images/Player.png";
constexpr auto PlAYER_BULLET__FILEPATH = "./Assets/Images/PlayerBullet.png";
constexpr auto BACKGROUND_FILEPATH = "./Assets/Images/Background.png";
constexpr auto PLAYER_SHOOT_SOUND_FILEPATH = "./Assets/Sounds/shoot.wav";
constexpr auto ENEMY_DEATH_SOUND_FILEPATH = "./Assets/Sounds/invaderkilled.wav";
constexpr auto BACKGROUND_MUSIC_SOUND_FILEPATH = "./Assets/Sounds/backgroundSong.wav";
constexpr auto ENEMY_MOVE_SOUND_FILEPATH = "./Assets/Sounds/invaderMove.wav";
constexpr auto ENEMY_MOVE_SOUND_X1_25_FILEPATH = "./Assets/Sounds/invaderMoveX1.25.wav";
constexpr auto ENEMY_MOVE_SOUND_X1_5_FILEPATH = "./Assets/Sounds/invaderMoveX1.5.wav";
constexpr auto ENEMY_MOVE_SOUND_X1_75_FILEPATH = "./Assets/Sounds/invaderMoveX1.75.wav";
constexpr auto ENEMY_MOVE_SOUND_X2_FILEPATH = "./Assets/Sounds/invaderMoveX2.wav";


constexpr float GlobalSize{ 40.f };
constexpr unsigned short ScreenHeight{ 1024 };
constexpr unsigned short ScreenWidth{ 720 };

constexpr float SwitchToNextTime{ 0.2f };
constexpr unsigned short PlayerStartingX = 512.f;
constexpr unsigned short PlayerStartingY = 650.f;





#endif // !GLOBAL_H

