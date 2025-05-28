#ifndef GAMIFICATION_H
#define GAMIFICATION_H

#include "flashcard.h"
#include <vector>
#include <string>

class Battle
{
public:
    Battle(std::vector<Flashcard> &userDeck, const std::string &deckName);
    void startBattle();
    int getFinalScore() const;

private:
    std::vector<Flashcard> battleDeck;
    std::string deckName;
    int playerHP;
    int enemyHP;
    int score;

    void battleLoop();
    bool answerQuestion(Flashcard &card);
    void calculateDamage(bool correct, float timeSpent);
    void showBattleStatus();
    void showResult();
};

#endif