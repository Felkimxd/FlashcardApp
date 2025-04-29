#include "flashcard.h"

Flashcard::Flashcard(std::string question, std::string answer, float grade) {
    this->question = question;
    this->answer = answer;
};

void Flashcard::setQuestion(std::string const &question){
    this->question = question;
}

void Flashcard::setAnswer(std::string const &answer) {
    this->answer = answer;
};

std::string const Flashcard::getQuestion() {

    return this->question;
};

std::string const Flashcard::getAnswer(){

    return this->answer;
}
