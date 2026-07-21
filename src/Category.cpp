#include "Category.h"
#include <iostream>
#include <optional>

Category::Category(sf::RenderWindow& window)
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

    title->setString("SELECT CATEGORY");
    title->setCharacterSize(52);
    title->setFillColor(sf::Color::White);
    title->setPosition({340.f, 50.f});

    // Buttons
    mathButton = Button(font, "MATHEMATICS",
                        {360.f, 60.f}, {430.f, 170.f});

    scienceButton = Button(font, "SCIENCE",
                           {360.f, 60.f}, {430.f, 260.f});

    historyButton = Button(font, "HISTORY",
                           {360.f, 60.f}, {430.f, 350.f});

    geographyButton = Button(font, "GEOGRAPHY",
                             {360.f, 60.f}, {430.f, 440.f});

    backButton = Button(font, "BACK",
                        {220.f, 60.f}, {500.f, 560.f});
}

CategoryAction Category::run()
{
    while (window.isOpen())
    {
        mathButton.update(window);
        scienceButton.update(window);
        historyButton.update(window);
        geographyButton.update(window);
        backButton.update(window);

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
                return CategoryAction::Back;
            }

            if (const auto* mousePressed =
                event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mathButton.isClicked(*mousePressed, window))
                {
                    return CategoryAction::Mathematics;
                }

                if (scienceButton.isClicked(*mousePressed, window))
                {
                    return CategoryAction::Science;
                }

                if (historyButton.isClicked(*mousePressed, window))
                {
                    return CategoryAction::History;
                }

                if (geographyButton.isClicked(*mousePressed, window))
                {
                    return CategoryAction::Geography;
                }

                if (backButton.isClicked(*mousePressed, window))
                {
                    return CategoryAction::Back;
                }
            }
        }

        window.clear();

        if (background)
            window.draw(*background);

        if (title)
            window.draw(*title);

        mathButton.draw(window);
        scienceButton.draw(window);
        historyButton.draw(window);
        geographyButton.draw(window);
        backButton.draw(window);

        window.display();
    }

    return CategoryAction::Back;
}