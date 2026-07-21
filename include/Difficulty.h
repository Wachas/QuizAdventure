#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <SFML/Graphics.hpp>
#include <optional>
#include "Button.h"
#include "DifficultyAction.h"

class Difficulty
{
public:
    Difficulty(sf::RenderWindow& window);
    DifficultyAction run();

private:
    sf::RenderWindow& window;

    sf::Texture backgroundTexture;
    sf::Font font;

    std::optional<sf::Sprite> background;
    std::optional<sf::Text> title;

    Button easyButton;
    Button mediumButton;
    Button hardButton;
    Button backButton;
};

#endif