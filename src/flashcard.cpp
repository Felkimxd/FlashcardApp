#include "flashcard.h"

Flashcard::Flashcard(int id, const std::string &question, const std::string &answer)
    : id(id), question(question), answer(answer) {}

int Flashcard::getId() const { return id; }
std::string Flashcard::getQuestion() const { return question; }
std::string Flashcard::getAnswer() const { return answer; }

void Flashcard::setQuestion(const std::string &question) { this->question = question; }
void Flashcard::setAnswer(const std::string &answer) { this->answer = answer; }