#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Constants.h"

namespace ApplesGame
{
    struct GameResources
    {
        GameResources();
        ~GameResources() = default;

        sf::Texture m_playerTexture;
        sf::Texture m_appleTexture;
        sf::Texture m_barrierTexture;

        sf::SoundBuffer m_eatAppleSoundBuffer;
        sf::SoundBuffer m_deathSoundBuffer;
        sf::SoundBuffer m_winSoundBuffer;

        sf::Sound m_eatAppleSound;
        sf::Sound m_deathSound;
        sf::Sound m_winSound;

        sf::Texture m_backgroundTexture;
        sf::Sprite m_backgroundSprite;

        sf::Font m_font;
    };

} // namespace ApplesGame