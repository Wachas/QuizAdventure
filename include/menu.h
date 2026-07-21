#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <optional>
#include "Button.h"
#include "MenuAction.h"

class Menu
{
public:
    Menu(sf::RenderWindow& window);
    MenuAction run();

private:
    sf::RenderWindow& window;

    sf::Texture backgroundTexture;
    sf::Font font;

    std::optional<sf::Sprite> background;
    std::optional<sf::Text> title;

    Button startButton;
    Button howButton;
    Button exitButton;
};

#endif