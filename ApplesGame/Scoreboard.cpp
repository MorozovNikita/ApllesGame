#include "Scoreboard.h"

#include "Constants.h"

#include <cassert>
#include <string>

namespace ApplesGame
{
    void Scoreboard::init(const int& totalApples)
    {
        assert(font.loadFromFile(RESOURCES_PATH + "\\Fonts\\PressStart2P-Regular.ttf"));

        scoreText.setFont(font);
        scoreText.setCharacterSize(FONT_SIZE);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setStyle(sf::Text::Bold);
        scoreText.setPosition(MARGIN, MARGIN);

        totalApples ? update(0, totalApples) : update(0);
    }

    void Scoreboard::update(int numEatenApples)
    {
        scoreText.setString("Apples: " + std::to_string(numEatenApples));
    }

    void Scoreboard::update(const int& numEatenApples, const int& totalApples)
    {
        scoreText.setString("Apples: " + std::to_string(numEatenApples) + '/' + std::to_string(totalApples));
    }

    void Scoreboard::draw(sf::RenderWindow& window)
    {
        window.draw(scoreText);
    }

} // namespace ApplesGame