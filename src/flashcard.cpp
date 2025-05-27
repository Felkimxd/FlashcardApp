#include "flashcard.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

Flashcard::Flashcard(int id,const std::string &question, const std::string &answer, float grade, int triesCounter, int estimatedTimeSeconds) {
    this->id = id;
    this->question = question;
    this->answer = answer;
    this->grade = grade;
    this->triesCounter = triesCounter;
    this->estimatedTimeSeconds = estimatedTimeSeconds;
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

        finalScore = (0.5f * normalizedTime + 0.5f * userFeedback)*10;
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

std::string const Flashcard::getQuestion() {

    return this->question;
};

std::string const Flashcard::getAnswer(){

    return this->answer;
}

int const Flashcard::getID(){

    return this->id;
}
float const Flashcard::getGrade(){

    return this->grade;
}
int const Flashcard::gettriesCounter(){

    return this->triesCounter;
}

int const Flashcard::getestimatedTIme(){

    return this->estimatedTimeSeconds;
}