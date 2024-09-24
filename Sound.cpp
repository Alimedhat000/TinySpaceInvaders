#include "Sound.h"

Sound::Sound()
{
    if (ShootSoundBuffer.loadFromFile(PLAYER_SHOOT_SOUND_FILEPATH))
    {
        ShootSound.setBuffer(ShootSoundBuffer);
        ShootSound.setVolume(30);
    }

    if (EnemyDeathSoundBuffer.loadFromFile(ENEMY_DEATH_SOUND_FILEPATH))
    {
        EnemyDeathSound.setBuffer(EnemyDeathSoundBuffer);
        EnemyDeathSound.setVolume(30);
    }

    if (BackGroundSoundBuffer.loadFromFile(BACKGROUND_MUSIC_SOUND_FILEPATH))
    {
        BackGroundSound.setBuffer(BackGroundSoundBuffer);
        BackGroundSound.setVolume(20);
    }

    if (EnemyMoveSoundBuffer.loadFromFile(ENEMY_MOVE_SOUND_FILEPATH))
    {
        EnemyMove125SoundBuffer.loadFromFile(ENEMY_MOVE_SOUND_X1_25_FILEPATH);
        EnemyMove150SoundBuffer.loadFromFile(ENEMY_MOVE_SOUND_X1_5_FILEPATH);
        EnemyMove175SoundBuffer.loadFromFile(ENEMY_MOVE_SOUND_X1_75_FILEPATH);
        EnemyMove200SoundBuffer.loadFromFile(ENEMY_MOVE_SOUND_X2_FILEPATH);

        EnemyMoveSound.setBuffer(EnemyMoveSoundBuffer);
        EnemyMoveSound.setVolume(30);
    }

    if (EnemyShootSoundBuffer.loadFromFile(ENEMY_SHOOT_SOUND_FILEPATH)) {
        EnemyShootSound.setBuffer(EnemyShootSoundBuffer);
        EnemyShootSound.setVolume(30);
    }
    if (HitSoundBuffer.loadFromFile(PLAYER_HIT_SOUND_FILEPATH)) {
        HitSound.setBuffer(HitSoundBuffer);
        HitSound.setVolume(30);
    }
}

void Sound::PlayShootSound()
{

    ShootSound.play();
}

void Sound::PlayhitSound()
{

    HitSound.play();
}

void Sound::PlayEnemyDeathSound()
{

    EnemyDeathSound.play();
}

void Sound::PlayEnemyShootSound()
{

    EnemyShootSound.play();
}

void Sound::PlayEnemyMoveSound()
{
    if (EnemyMoveSound.getStatus() != sf::Sound::Playing) {
        EnemyMoveSound.play();
    }
}

void Sound::SetEnemyMoveSoundSpeed(int DeathCount)
{
    const sf::SoundBuffer* newBuffer = nullptr;

    if (DeathCount <= 10) {
        newBuffer = &EnemyMoveSoundBuffer;
    }
    else if (DeathCount <= 20) {
        newBuffer = &EnemyMove125SoundBuffer;
    }
    else if (DeathCount <= 30) {
        newBuffer = &EnemyMove150SoundBuffer;
    }
    else if (DeathCount <= 40) {
        newBuffer = &EnemyMove175SoundBuffer;
    }
    else {
        newBuffer = &EnemyMove200SoundBuffer;
    }

    // Only change the buffer if it's different from the current buffer
    if (CurEnemyMoveBuffer != newBuffer) {
        EnemyMoveSound.setBuffer(*newBuffer);
        CurEnemyMoveBuffer = newBuffer; // Update the current buffer
    }
}



void Sound::PlayBackgroundSound()
{

    if (BackGroundSound.getStatus() != sf::Sound::Playing) {
        BackGroundSound.play();
    }

}

void Sound::StopBackgroundSound()
{
    BackGroundSound.stop();
}
