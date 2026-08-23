#include "NameInputScreen.h"

#include "Constants.h"
#include "Math.h"

namespace ApplesGame
{
    NameInputScreen::NameInputScreen(const sf::Font& font)
        : m_font(font)
    {
        init();
    }

    void NameInputScreen::init()
    {
        const float centerX = SCREEN_WIDTH / 2.f;

        // header
        m_titleText.setFont(m_font);
        m_titleText.setCharacterSize(NAME_INPUT_TITLE_SIZE);
        m_titleText.setFillColor(titleColor);
        m_titleText.setString("GAME OVER"s);
        centerTextHorizontally(m_titleText, centerX, 100.f);

        // score
        m_scoreText.setFont(m_font);
        m_scoreText.setCharacterSize(NAME_INPUT_TEXT_SIZE);
        m_scoreText.setFillColor(textColor);

        // label
        m_labelText.setFont(m_font);
        m_labelText.setCharacterSize(NAME_INPUT_TEXT_SIZE);
        m_labelText.setFillColor(textColor);
        m_labelText.setString("Enter your name:"s);
        centerTextHorizontally(m_labelText, centerX, 300.f);

        // name
        m_nameText.setFont(m_font);
        m_nameText.setCharacterSize(NAME_INPUT_TEXT_SIZE);
        m_nameText.setFillColor(sf::Color::Yellow);

        // hint
        m_hintText.setFont(m_font);
        m_hintText.setCharacterSize(14);
        m_hintText.setFillColor(hintColor);
        m_hintText.setString("ENTER - confirm, ESC - skip"s);
        centerTextHorizontally(m_hintText, centerX, SCREEN_HEIGHT - 60.f);
    }

    std::string NameInputScreen::run(sf::RenderWindow& window, int score)
    {
        m_playerName.clear();
        bool running = true;

        while (running && window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                    return {};
                }

                handleInput(event);

                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Enter && !m_playerName.empty())
                        return m_playerName;
                    else if (event.key.code == sf::Keyboard::Escape)
                        return DEFAULT_NAME;
                }
            }

            draw(window, score);
        }

        return {};
    }

    void NameInputScreen::handleInput(const sf::Event& event)
    {
        if (event.type == sf::Event::TextEntered)
        {
            sf::Uint32 unicode = event.text.unicode;

            if (unicode == 8 && !m_playerName.empty())
            {
                m_playerName.pop_back();
            }

            else if (unicode >= 32 && unicode < 127)
            {
                if (m_playerName.size() < NAME_INPUT_MAX_NAME_LENGTH)
                {
                    m_playerName += static_cast<char>(unicode);
                }
            }
        }
    }

    void NameInputScreen::updateNameText()
    {
        m_nameText.setString(m_playerName + '_');
        centerTextHorizontally(m_nameText, SCREEN_WIDTH / 2.f, 350.f);
    }

    void NameInputScreen::draw(sf::RenderWindow& window, int score) 
    {
        window.clear(backgroundColor);

        m_scoreText.setString("Score: "s + std::to_string(score));
        centerTextHorizontally(m_scoreText, SCREEN_WIDTH / 2.f, 180.f);

        m_nameText.setString(m_playerName + "_");
        centerTextHorizontally(m_nameText, SCREEN_WIDTH / 2.f, 350.f);

        window.draw(m_titleText);
        window.draw(m_scoreText);
        window.draw(m_labelText);
        window.draw(m_nameText);
        window.draw(m_hintText);

        window.display();
    }

} // namespace ApplesGame