#include "GameResources.h"

#include <cassert>

namespace ApplesGame
{
    GameResources::GameResources()
    {
        assert(m_playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
        assert(m_appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
        assert(m_barrierTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));
        assert(m_backgroundTexture.loadFromFile(RESOURCES_PATH + "\\Grass.png"));

        assert(m_eatAppleSoundBuffer.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"));
        assert(m_deathSoundBuffer.loadFromFile(RESOURCES_PATH + "\\Death.wav"));
        assert(m_winSoundBuffer.loadFromFile(RESOURCES_PATH + "\\Win.wav"));

        assert(m_font.loadFromFile(RESOURCES_PATH + "\\Fonts\\PressStart2P-Regular.ttf"));

        m_eatAppleSound.setBuffer(m_eatAppleSoundBuffer);
        m_deathSound.setBuffer(m_deathSoundBuffer);
        m_winSound.setBuffer(m_winSoundBuffer);

        m_backgroundSprite.setTexture(m_backgroundTexture);
    }
}