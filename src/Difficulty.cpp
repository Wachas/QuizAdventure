#include "Difficulty.h"
#include <iostream>
#include <optional>

Difficulty::Difficulty(sf::RenderWindow& window)
    : window(window)
{
    // Background
    if (!backgroundTexture.loadFromFile("assets/images/background.png"))
    {
        std::cout << "Failed to load background image!\n";
    }

    background.emplace(backgroundTexture);

    background->setScale({
        1280.f / backgroundTexture.getSize().x,
        720.f / backgroundTexture.getSize().y
    });

    // Font
    if (!font.openFromFile("assets/fonts/Poppins-Bold.ttf"))
    {
        std::cout << "Failed to load font!\n";
    }

    // Title
    title.emplace(font);

    title->setString("SELECT DIFFICULTY");
    title->setCharacterSize(52);
    title->setFillColor(sf::Color::White);
    title->setPosition({320.f, 50.f});

    // Buttons
    easyButton = Button(font, "EASY",
                        {360.f, 60.f}, {430.f, 220.f});

    mediumButton = Button(font, "MEDIUM",
                          {360.f, 60.f}, {430.f, 320.f});

    hardButton = Button(font, "HARD",
                        {360.f, 60.f}, {430.f, 420.f});

    backButton = Button(font, "BACK",
                        {220.f, 60.f}, {500.f, 560.f});
}

DifficultyAction Difficulty::run()
{
    while (window.isOpen())
    {
        easyButton.update(window);
        mediumButton.update(window);
        hardButton.update(window);
        backButton.update(window);

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
                return DifficultyAction::Back;
            }

            if (const auto* mousePressed =
                event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (easyButton.isClicked(*mousePressed, window))
                {
                    return DifficultyAction::Easy;
                }

                if (mediumButton.isClicked(*mousePressed, window))
                {
                    return DifficultyAction::Medium;
                }

                if (hardButton.isClicked(*mousePressed, window))
                {
                    return DifficultyAction::Hard;
                }

                if (backButton.isClicked(*mousePressed, window))
                {
                    return DifficultyAction::Back;
                }
            }
        }

        window.clear();

        if (background)
            window.draw(*background);

        if (title)
            window.draw(*title);

        easyButton.draw(window);
        mediumButton.draw(window);
        hardButton.draw(window);
        backButton.draw(window);

        window.display();
    }

    return DifficultyAction::Back;
}