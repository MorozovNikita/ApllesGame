#include "Scoreboard.h"

#include "Constants.h"

#include <cassert>
#include <string>

namespace ApplesGame
{
    void Scoreboard::init(const sf::Font& font, const int& totalApples)
    {
        m_scoreText.setFont(font);
        m_scoreText.setCharacterSize(FONT_SIZE);
        m_scoreText.setFillColor(sf::Color::White);
        m_scoreText.setStyle(sf::Text::Bold);
        m_scoreText.setPosition(MARGIN, MARGIN);

        totalApples ? update(0, totalApples) : update(0);
    }

    void Scoreboard::update(int numEatenApples)
    {
        m_scoreText.setString("Apples: " + std::to_string(numEatenApples));
    }

    void Scoreboard::update(const int& numEatenApples, const int& totalApples)
    {
        m_scoreText.setString("Apples: " + std::to_string(numEatenApples) + '/' + std::to_string(totalApples));
    }

    void Scoreboard::draw(sf::RenderWindow& window)
    {
        window.draw(m_scoreText);
    }

} // namespace ApplesGame