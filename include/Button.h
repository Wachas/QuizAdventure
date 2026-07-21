#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <optional>

class Button
{
public:
    Button();

    Button(
        const sf::Font& font,
        const std::string& text,
        sf::Vector2f size,
        sf::Vector2f position);

    void draw(sf::RenderWindow& window);

    void update(sf::RenderWindow& window);

    bool isHovered(sf::RenderWindow& window);

    bool isClicked(const sf::Event::MouseButtonPressed& event,
                   sf::RenderWindow& window);

    void setText(const std::string& text);
    std::string getText() const;

    // NEW
    void setColor(const sf::Color& color);
    void resetColor();

private:
    sf::RectangleShape box;
    std::optional<sf::Text> label;

    sf::Color normalColor;
    sf::Color hoverColor;
};

#endif