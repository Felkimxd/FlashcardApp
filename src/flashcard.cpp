#include "flashcard.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

Flashcard::Flashcard(std::string question, std::string answer) {
    this->question = question;
    this->answer = answer;
    this->grade = 0;
    this->triesCounter = 0;
    this->estimatedTimeSeconds = 0;
};

void Flashcard::setQuestion(std::string const &question){
    this->question = question;
};

void Flashcard::setAnswer(std::string const &answer) {
    this->answer = answer;
};

void Flashcard::gradeCalc(float const &timeTakeIt, float const &userFeedback)
{
    float finalScore = 0.0f;
    float normalizedTime = 0.0f;

    try
    {   
        if (this->estimatedTimeSeconds == 0)
        {
            throw std::domain_error("The time to solve the question is 0. Please check this");
        }

        normalizedTime = std::max(0.0, 1.0 - (timeTakeIt / this->estimatedTimeSeconds));

        finalScore = 0.5f * normalizedTime + 0.5f * userFeedback;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Zero Division " << e.what() << '\n';
    }

    this->grade = finalScore;
};

void Flashcard::IncrementTries() {
    this->triesCounter ++;
};

void Flashcard::updateEstimatedTime(int const &stimatedTime) {
    this->estimatedTimeSeconds = stimatedTime;
};

std::string const Flashcard::getQuestion() {

    return this->question;
};

std::string const Flashcard::getAnswer(){

    return this->answer;
}