#pragma once
#include <SFML/Audio.hpp>
#include "Global.h"
#include <iostream>

class Sound
{
public:
    Sound();

    void PlayShootSound();
    void PlayhitSound();
    void PlayEnemyDeathSound();
    void PlayEnemyMoveSound();
    void SetEnemyMoveSoundSpeed(int DeathCount);
    void PlayEnemyShootSound();
    void PlayBackgroundSound();
    void StopBackgroundSound();

private:

    sf::SoundBuffer ShootSoundBuffer;
    sf::Sound ShootSound;
    sf::SoundBuffer HitSoundBuffer;
    sf::Sound HitSound;


    sf::SoundBuffer EnemyDeathSoundBuffer;
    sf::Sound EnemyDeathSound;

    sf::SoundBuffer BackGroundSoundBuffer;
    sf::Sound BackGroundSound;

    sf::SoundBuffer EnemyMoveSoundBuffer;
    sf::SoundBuffer EnemyMove125SoundBuffer;
    sf::SoundBuffer EnemyMove150SoundBuffer;
    sf::SoundBuffer EnemyMove175SoundBuffer;
    sf::SoundBuffer EnemyMove200SoundBuffer;
    const sf::SoundBuffer* CurEnemyMoveBuffer = nullptr;
    sf::Sound EnemyMoveSound;

    sf::SoundBuffer EnemyShootSoundBuffer;
    sf::Sound EnemyShootSound;

};

