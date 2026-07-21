#include "menu.h"
#include "MenuAction.h"
#include "HowToPlay.h"
#include "Category.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Difficulty.h"
#include "DifficultyAction.h"
#include "Game.h"
#include <iostream>
#include <filesystem>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({1280, 720}),
        "Quiz Adventure"
    );

    // --- MENU BACKGROUND MUSIC ---
    sf::Music menuBgm;
    if (!menuBgm.openFromFile("assets/sounds/menu_bgm.wav"))
    {
        std::cout << "Failed to load menu background music!\n";
    }
    else
    {
        menuBgm.setLooping(true);
        menuBgm.setVolume(20.f);
        menuBgm.play();
    }

    while (window.isOpen())
    {
        Menu menu(window);
        MenuAction action = menu.run();

        switch (action)
        {
        case MenuAction::StartGame:
        {
            Category category(window);
            CategoryAction categoryAction = category.run();

            if (categoryAction == CategoryAction::Back)
                break;

            Difficulty difficulty(window);
            DifficultyAction difficultyAction = difficulty.run();

            if (difficultyAction == DifficultyAction::Back)
                break;

            std::string filename;

            // Category
            if (categoryAction == CategoryAction::Mathematics)
                filename = "data/Math/";
            else if (categoryAction == CategoryAction::Science)
                filename = "data/Science/";
            else if (categoryAction == CategoryAction::History)
                filename = "data/History/";
            else if (categoryAction == CategoryAction::Geography)
                filename = "data/Geography/";

            // Difficulty
            if (difficultyAction == DifficultyAction::Easy)
                filename += "Easy.txt";
            else if (difficultyAction == DifficultyAction::Medium)
                filename += "Medium.txt";
            else if (difficultyAction == DifficultyAction::Hard)
                filename += "Hard.txt";

            // PAUSE menu music when starting the quiz
            menuBgm.pause();

            Game game(window);
            game.loadQuiz(filename);
            std::cout << "Loading file: " << filename << std::endl;
            game.run();

            // RESUME menu music when returning from the quiz
            menuBgm.play();

            break;
        }

        case MenuAction::HowToPlay:
        {
            HowToPlay how(window);
            how.run();
            break;
        }

        case MenuAction::Exit:
            window.close();
            break;

        default:
            break;
        }
    }

    return 0;
}