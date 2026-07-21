#include "Button.h"

Button::Button()
{
}

Button::Button(
    const sf::Font& font,
    const std::string& text,
    sf::Vector2f size,
    sf::Vector2f position)
{
    normalColor = sf::Color(40, 60, 120);
    hoverColor = sf::Color(70, 100, 180);

    box.setSize(size);
    box.setPosition(position);
    box.setFillColor(normalColor);
    box.setOutlineThickness(2.f);
    box.setOutlineColor(sf::Color::White);

    label.emplace(font);

    label->setString(text);
    label->setCharacterSize(34);
    label->setFillColor(sf::Color::White);

    sf::FloatRect bounds = label->getLocalBounds();

    label->setOrigin({
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f
    });

    label->setPosition({
        position.x + size.x / 2.f,
        position.y + size.y / 2.f
    });
}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(box);

    if (label)
        window.draw(*label);
}

bool Button::isHovered(sf::RenderWindow& window)
{
    sf::Vector2f mouse =
        window.mapPixelToCoords(sf::Mouse::getPosition(window));

    return box.getGlobalBounds().contains(mouse);
}

void Button::update(sf::RenderWindow& window)
{
    if (isHovered(window))
        box.setFillColor(hoverColor);
    else
        box.setFillColor(normalColor);
}

bool Button::isClicked(const sf::Event::MouseButtonPressed& event,
                       sf::RenderWindow& window)
{
    return event.button == sf::Mouse::Button::Left &&
           isHovered(window);
}

// ===============================
// NEW FUNCTIONS
// ===============================

void Button::setText(const std::string& text)
{
    if (!label)
        return;

    label->setString(text);

    sf::FloatRect bounds = label->getLocalBounds();

    label->setOrigin({
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f
    });

    label->setPosition({
        box.getPosition().x + box.getSize().x / 2.f,
        box.getPosition().y + box.getSize().y / 2.f
    });
}

std::string Button::getText() const
{
    if (!label)
        return "";

    return label->getString().toAnsiString();
}

void Button::setColor(const sf::Color& color)
{
    box.setFillColor(color);
}

void Button::resetColor()
{
    box.setFillColor(normalColor);
}