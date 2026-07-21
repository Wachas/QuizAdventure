#include "HowToPlay.h"
#include <iostream>

HowToPlay::HowToPlay(sf::RenderWindow& window)
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
    title->setString("HOW TO PLAY");
    title->setCharacterSize(54);
    title->setFillColor(sf::Color::White);
    title->setPosition({400.f, 50.f});

    // Instructions
    instructions.emplace(font);
    instructions->setCharacterSize(28);
    instructions->setFillColor(sf::Color::White);
    instructions->setPosition({180.f, 170.f});

    instructions->setString(
        "1. Select a quiz category.\n\n"
        "2. Answer each question before the timer ends.\n\n"
        "3. Each correct answer gives 10 points.\n\n"
        "4. Wrong answers give 0 points.\n\n"
        "5. Your final score will be shown at the end."
    );

    // Back button
    backButton = Button(
        font,
        "BACK",
        {220.f, 60.f},
        {530.f, 600.f}
    );
}

void HowToPlay::run()
{
    while (window.isOpen())
    {
        backButton.update(window);

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
                return;
            }

            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (backButton.isClicked(*mousePressed, window))
                {
                    return;
                }
            }
        }

        window.clear();

        if (background)
            window.draw(*background);

        if (title)
            window.draw(*title);

        if (instructions)
            window.draw(*instructions);

        backButton.draw(window);

        window.display();
    }
}