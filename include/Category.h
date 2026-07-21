#ifndef CATEGORY_H
#define CATEGORY_H

#include <SFML/Graphics.hpp>
#include <optional>
#include "Button.h"
#include "CategoryAction.h"

class Category
{
public:
    Category(sf::RenderWindow& window);
    CategoryAction run();

private:
    sf::RenderWindow& window;

    sf::Texture backgroundTexture;
    std::optional<sf::Sprite> background;

    sf::Font font;

    std::optional<sf::Text> title;

    Button mathButton;
    Button scienceButton;
    Button historyButton;
    Button geographyButton;
    Button backButton;
};

#endif