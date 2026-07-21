#pragma once

#include <string>
#include <vector>

class Question
{
private:
    std::string question;
    std::vector<std::string> options;
    int correctAnswer;

public:
    Question();

    Question(
        const std::string& question,
        const std::vector<std::string>& options,
        int correctAnswer);

    std::string getQuestion() const;
    std::vector<std::string> getOptions() const;
    int getCorrectAnswer() const;
};