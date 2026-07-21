#include "QuestionLoader.h"

#include <fstream>
#include <iostream>

std::vector<Question> QuestionLoader::loadQuestions(const std::string& filename)
{
    std::vector<Question> questions;

    std::ifstream file(filename);

    if (!file)
    {
        std::cout << "Cannot open file: " << filename << std::endl;
        return questions;
    }

    while (true)
    {
        std::string questionText;

        if (!std::getline(file, questionText))
            break;

        if (questionText.empty())
            continue;

        std::vector<std::string> options(4);

        std::getline(file, options[0]);
        std::getline(file, options[1]);
        std::getline(file, options[2]);
        std::getline(file, options[3]);

        std::string answer;
        std::getline(file, answer);

        int correct = answer[0] - 'A';

        questions.emplace_back(questionText, options, correct);

        std::string blank;
        std::getline(file, blank);
    }

    std::cout << questions.size()
              << " questions loaded.\n";

    return questions;
}