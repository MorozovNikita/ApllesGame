#include "Scoreboard.h"

#include "Constants.h"

#include <cassert>
#include <string>

namespace ApplesGame
{
    void Scoreboard::init()
    {
        assert(font.loadFromFile(RESOURCES_PATH + "\\Fonts\\Agitpropc.otf"));

        scoreText.setFont(font);
        scoreText.setCharacterSize(FONT_SIZE);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setStyle(sf::Text::Bold);
        scoreText.setPosition(MARGIN, MARGIN);

        update(0);
    }

    void Scoreboard::update(int numEatenApples)
    {
        scoreText.setString("Apples: " + std::to_string(numEatenApples));
    }

    void Scoreboard::draw(sf::RenderWindow& window)
    {
        window.draw(scoreText);
    }

} // namespace ApplesGame