#include "Questions.h"

Question::Question()
    : correctAnswer(0)
{
}

Question::Question(
    const std::string& question,
    const std::vector<std::string>& options,
    int correctAnswer)
    : question(question),
      options(options),
      correctAnswer(correctAnswer)
{
}

std::string Question::getQuestion() const
{
    return question;
}

std::vector<std::string> Question::getOptions() const
{
    return options;
}

int Question::getCorrectAnswer() const
{
    return correctAnswer;
}