#include "Game.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <thread>
#include <chrono>

Game::Game(sf::RenderWindow& window)
    : window(window),
      optionA(), optionB(), optionC(), optionD(),
      abortButton(), playAgainButton(), mainMenuButton(),
      correctSound(correctBuffer), wrongSound(wrongBuffer),
      currentQuestion(0), score(0), isGameOver(false), isAnswerProcessing(false)
{
    // 1. Load Background
    if (!backgroundTexture.loadFromFile("assets/images/background.png"))
        std::cout << "Failed to load background image!\n";

    background.emplace(backgroundTexture);
    background->setScale({
        1280.f / backgroundTexture.getSize().x,
        720.f / backgroundTexture.getSize().y
    });

    // 2. Load Font
    if (!font.openFromFile("assets/fonts/Poppins-Bold.ttf"))
        std::cout << "Failed to load font!\n";

    // 3. Load Audio
    if (!correctBuffer.loadFromFile("assets/sounds/correct.wav"))
        std::cout << "Failed to load correct.wav!\n";

    if (!wrongBuffer.loadFromFile("assets/sounds/wrong.wav"))
        std::cout << "Failed to load wrong.wav!\n";

    // --- GAMEPLAY BACKGROUND MUSIC ---
    // Tries game_bgm.wav first; falls back to backround.wav if not found
    if (!bgm.openFromFile("assets/sounds/game_bgm.wav"))
    {
        if (!bgm.openFromFile("assets/sounds/backround.wav"))
        {
            std::cout << "Failed to load gameplay music (checked game_bgm.wav and backround.wav)!\n";
        }
        else
        {
            bgm.setLooping(true);
            bgm.setVolume(20.f);
            bgm.play();
        }
    }
    else
    {
        bgm.setLooping(true);
        bgm.setVolume(20.f);
        bgm.play();
    }

    // 4. Texts
    questionText.emplace(font);
    questionText->setCharacterSize(32);
    questionText->setFillColor(sf::Color::White);
    questionText->setPosition({100.f, 80.f});

    questionNumberText.emplace(font);
    questionNumberText->setCharacterSize(22);
    questionNumberText->setFillColor(sf::Color::Yellow);
    questionNumberText->setPosition({100.f, 20.f});

    scoreText.emplace(font);
    scoreText->setCharacterSize(22);
    scoreText->setFillColor(sf::Color::Green);
    scoreText->setPosition({950.f, 20.f});

    timerText.emplace(font);
    timerText->setCharacterSize(22);
    timerText->setFillColor(sf::Color::Cyan);
    timerText->setPosition({550.f, 20.f});

    gameOverText.emplace(font);
    gameOverText->setCharacterSize(42);
    gameOverText->setFillColor(sf::Color::Yellow);
    gameOverText->setPosition({380.f, 150.f});

    // 5. Buttons
    // Answer options
    optionA = Button(font, "", {500.f, 60.f}, {390.f, 220.f});
    optionB = Button(font, "", {500.f, 60.f}, {390.f, 320.f});
    optionC = Button(font, "", {500.f, 60.f}, {390.f, 420.f});
    optionD = Button(font, "", {500.f, 60.f}, {390.f, 520.f});

    // Shortened "Abort Game" to "Abort"
    abortButton     = Button(font, "Abort",      {120.f, 45.f}, {50.f,  630.f});
    playAgainButton = Button(font, "Play Again", {250.f, 65.f}, {350.f, 420.f});
    mainMenuButton  = Button(font, "Main Menu",  {250.f, 65.f}, {680.f, 420.f});
}

void Game::loadQuiz(const std::string& filename)
{
    currentFilename = filename;
    QuestionLoader loader;
    questions = loader.loadQuestions(filename);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(questions.begin(), questions.end(), g);

    if (questions.size() > 10)
        questions.resize(10);

    currentQuestion = 0;
    score = 0;
    isGameOver = false;

    showCurrentQuestion();
}

void Game::showCurrentQuestion()
{
    if (questions.empty()) return;

    Question& q = questions[currentQuestion];
    questionText->setString(q.getQuestion());

    questionNumberText->setString(
        "Question " + std::to_string(currentQuestion + 1) + " / " + std::to_string(questions.size())
    );
    scoreText->setString("Score : " + std::to_string(score));

    auto options = q.getOptions();
    optionA.setText(options[0]);
    optionB.setText(options[1]);
    optionC.setText(options[2]);
    optionD.setText(options[3]);

    // Reset clock for new question
    questionClock.restart();
}

void Game::checkAnswer(int selected)
{
    isAnswerProcessing = true;
    int correct = questions[currentQuestion].getCorrectAnswer();

    optionA.resetColor(); optionB.resetColor();
    optionC.resetColor(); optionD.resetColor();

    Button* buttons[4] = { &optionA, &optionB, &optionC, &optionD };

    if (selected >= 0 && selected == correct)
    {
        score++;
        buttons[selected]->setColor(sf::Color::Green);
        correctSound.play();
    }
    else
    {
        if (selected >= 0)
            buttons[selected]->setColor(sf::Color::Red);
        buttons[correct]->setColor(sf::Color::Green);
        wrongSound.play();
    }

    scoreText->setString("Score : " + std::to_string(score));

    // Render answer feedback state
    window.clear();
    if (background) window.draw(*background);
    if (questionNumberText) window.draw(*questionNumberText);
    if (scoreText) window.draw(*scoreText);
    if (timerText) window.draw(*timerText);
    if (questionText) window.draw(*questionText);

    optionA.draw(window); optionB.draw(window);
    optionC.draw(window); optionD.draw(window);
    abortButton.draw(window);
    window.display();

    std::this_thread::sleep_for(std::chrono::milliseconds(900));

    optionA.resetColor(); optionB.resetColor();
    optionC.resetColor(); optionD.resetColor();

    currentQuestion++;

    if (currentQuestion >= static_cast<int>(questions.size()))
    {
        isGameOver = true;
        gameOverText->setString(
            "   QUIZ COMPLETED!\n\n Your Final Score: " +
            std::to_string(score) + " / " + std::to_string(questions.size())
        );
    }
    else
    {
        showCurrentQuestion();
    }

    isAnswerProcessing = false;
}

void Game::handleTimeOut()
{
    checkAnswer(-1);
}

void Game::restartGame()
{
    loadQuiz(currentFilename);
}

void Game::run()
{
    while (window.isOpen())
    {
        // ----------------------------------------------------
        // 1. GAME OVER SCREEN HANDLER
        // ----------------------------------------------------
        if (isGameOver)
        {
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                {
                    bgm.stop();
                    window.close();
                    return;
                }

                if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>())
                {
                    if (playAgainButton.isClicked(*mouse, window))
                    {
                        restartGame();
                    }
                    else if (mainMenuButton.isClicked(*mouse, window))
                    {
                        bgm.stop();
                        return; // Returns back to main.cpp loop
                    }
                }
            }

            playAgainButton.update(window);
            mainMenuButton.update(window);

            window.clear();
            if (background) window.draw(*background);
            if (gameOverText) window.draw(*gameOverText);
            playAgainButton.draw(window);
            mainMenuButton.draw(window);
            window.display();

            continue;
        }

        // ----------------------------------------------------
        // 2. ACTIVE QUIZ GAMEPLAY HANDLER
        // ----------------------------------------------------
        // Update Timer
        float remainingTime = timeLimit - questionClock.getElapsedTime().asSeconds();
        if (remainingTime <= 0.0f && !isAnswerProcessing)
        {
            handleTimeOut();
            continue;
        }

        int secondsLeft = static_cast<int>(std::max(0.0f, remainingTime));
        timerText->setString("Time Left: " + std::to_string(secondsLeft) + "s");

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                bgm.stop();
                window.close();
                return;
            }

            if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (!isAnswerProcessing)
                {
                    if (optionA.isClicked(*mouse, window))       checkAnswer(0);
                    else if (optionB.isClicked(*mouse, window))  checkAnswer(1);
                    else if (optionC.isClicked(*mouse, window))  checkAnswer(2);
                    else if (optionD.isClicked(*mouse, window))  checkAnswer(3);
                    else if (abortButton.isClicked(*mouse, window))
                    {
                        bgm.stop();
                        return; // Quits directly back to Main Menu
                    }
                }
            }
        }

        optionA.update(window); optionB.update(window);
        optionC.update(window); optionD.update(window);
        abortButton.update(window);

        window.clear();
        if (background) window.draw(*background);
        if (questionNumberText) window.draw(*questionNumberText);
        if (scoreText) window.draw(*scoreText);
        if (timerText) window.draw(*timerText);
        if (questionText) window.draw(*questionText);

        optionA.draw(window); optionB.draw(window);
        optionC.draw(window); optionD.draw(window);
        abortButton.draw(window);

        window.display();
    }

    bgm.stop();
}