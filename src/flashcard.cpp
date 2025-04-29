#include "flashcard.h"

Flashcard::Flashcard(std::string question, std::string answer) {
    this->question = question;
    this->answer = answer;
    this->grade = 0;
    this->triesCounter = 0;
    this->stimatedTimeSeconds = 0;
};

void Flashcard::setQuestion(std::string const &question){
    this->question = question;
}

void Flashcard::setAnswer(std::string const &answer) {
    this->answer = answer;
};

void Flashcard::gradeCalc()
{
    // I dont know
};

void Flashcard::addCounter() {
    this->triesCounter ++;
};

void Flashcard::setTime(int const &stimatedTime) {
    this->stimatedTimeSeconds = stimatedTime;
};

std::string const Flashcard::getQuestion() {

    return this->question;
};

std::string const Flashcard::getAnswer(){

    return this->answer;
}

