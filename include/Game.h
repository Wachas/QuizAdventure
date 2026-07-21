#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <optional>
#include <vector>
#include <string>

#include "Questions.h"
#include "QuestionLoader.h"
#include "Button.h"

class Game
{
public:
    Game(sf::RenderWindow& window);

    void loadQuiz(const std::string& filename);
    void run();

private:
    sf::RenderWindow& window;

    // Background & Font
    sf::Texture backgroundTexture;
    std::optional<sf::Sprite> background;
    sf::Font font;

    // UI Displays
    std::optional<sf::Text> questionText;
    std::optional<sf::Text> questionNumberText;
    std::optional<sf::Text> scoreText;
    std::optional<sf::Text> timerText;
    std::optional<sf::Text> gameOverText;

    // Answer Buttons
    Button optionA;
    Button optionB;
    Button optionC;
    Button optionD;

    // In-game Utility Buttons
    Button abortButton;

    // End Game Buttons
    Button playAgainButton;
    Button mainMenuButton;

    // Audio
    sf::SoundBuffer correctBuffer;
    sf::SoundBuffer wrongBuffer;
    sf::Sound correctSound;
    sf::Sound wrongSound;
    sf::Music bgm;

    // Quiz Data & State
    std::vector<Question> questions;
    int currentQuestion;
    int score;
    bool isGameOver;
    std::string currentFilename;

    // Timer Variables
    sf::Clock questionClock;
    const float timeLimit = 15.0f; // 15 seconds per question
    bool isAnswerProcessing;

    void showCurrentQuestion();
    void checkAnswer(int selected);
    void handleTimeOut();
    void restartGame();
};

#endif