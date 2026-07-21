#ifndef HOWTOPLAY_H
#define HOWTOPLAY_H

#include <SFML/Graphics.hpp>
#include <optional>
#include "Button.h"

class HowToPlay
{
public:
    HowToPlay(sf::RenderWindow& window);
    void run();

private:
    sf::RenderWindow& window;

    sf::Texture backgroundTexture;
    std::optional<sf::Sprite> background;

    sf::Font font;
    std::optional<sf::Text> title;
    std::optional<sf::Text> instructions;

    Button backButton;
};

#endif