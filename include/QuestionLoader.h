#ifndef QUESTIONLOADER_H
#define QUESTIONLOADER_H

#include <vector>
#include <string>
#include "Questions.h"

class QuestionLoader
{
public:
    std::vector<Question> loadQuestions(const std::string& filename);
};

#endif