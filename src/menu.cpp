#include "menu.h"
#include <iostream>
#include <optional>

Menu::Menu(sf::RenderWindow& window)
    : window(window)
{
    // Load background
    if (!backgroundTexture.loadFromFile("assets/images/background.png"))
    {
        std::cout << "Failed to load background image!\n";
    }

    background.emplace(backgroundTexture);

    background->setScale({
        1280.f / backgroundTexture.getSize().x,
        720.f / backgroundTexture.getSize().y
    });

    // Load font
    if (!font.openFromFile("assets/fonts/Poppins-Bold.ttf"))
    {
        std::cout << "Failed to load font!\n";
    }

    // Title
    title.emplace(font);

    title->setString("QUIZ ADVENTURE");
    title->setCharacterSize(60);
    title->setFillColor(sf::Color::White);
    title->setPosition({310.f, 50.f});

    // Create Buttons
    startButton = Button(
        font,
        "START GAME",
        {360.f, 60.f},
        {430.f, 270.f}
    );

    howButton = Button(
        font,
        "HOW TO PLAY",
        {360.f, 60.f},
        {430.f, 350.f}
    );

    exitButton = Button(
        font,
        "EXIT",
        {360.f, 60.f},
        {430.f, 430.f}
    );
}

MenuAction Menu::run()
{
    while (window.isOpen())
    {
        // Update button hover effects
        startButton.update(window);
        howButton.update(window);
        exitButton.update(window);

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                return MenuAction::Exit;
            }

            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (startButton.isClicked(*mousePressed, window))
                {
                    return MenuAction::StartGame;
                }

                if (howButton.isClicked(*mousePressed, window))
                {
                    return MenuAction::HowToPlay;
                }

                if (exitButton.isClicked(*mousePressed, window))
                {
                    return MenuAction::Exit;
                }
            }
        }
        

        window.clear();

        if (background)
            window.draw(*background);

        if (title)
            window.draw(*title);

        startButton.draw(window);
        howButton.draw(window);
        exitButton.draw(window);

        window.display();
    }
    return MenuAction::Exit;
}