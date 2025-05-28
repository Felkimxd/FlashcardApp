#include "gamification.h"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>

Battle::Battle(std::vector<Flashcard> &userDeck, const std::string &deckName)
    : battleDeck(userDeck), deckName(deckName), playerHP(100), enemyHP(100), score(0)
{
    // Mezclar el deck para tener preguntas aleatorias
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(battleDeck.begin(), battleDeck.end(), std::default_random_engine(seed));
}

void Battle::startBattle()
{
    std::cout << "\n=== BATTLE MODE: " << deckName << " ===" << std::endl;
    std::cout << "Prepare to the knowledge duel!" << std::endl;
    battleLoop();
}

void Battle::battleLoop()
{
    for (auto &card : battleDeck)
    {
        if (playerHP <= 0 || enemyHP <= 0)
            break;

        showBattleStatus();
        bool correct = answerQuestion(card);
        auto startTime = std::chrono::high_resolution_clock::now();

        auto endTime = std::chrono::high_resolution_clock::now();
        float timeSpent = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();

        calculateDamage(correct, timeSpent);
    }
    showResult();
}

bool Battle::answerQuestion(Flashcard &card)
{
    std::cout << "\nQuestion: " << card.getQuestion() << std::endl;
    std::cout << "Estimated time: " << card.getestimatedTIme() << " seconds" << std::endl;

    std::string userAnswer;
    std::cout << "Answer: ";
    std::getline(std::cin, userAnswer);

    return userAnswer == card.getAnswer();
}

void Battle::calculateDamage(bool correct, float timeSpent)
{
    if (correct)
    {
        int damage = 20; // Base Damage
        if (timeSpent < 5)
            damage += 10; // Speed Bonus
        enemyHP -= damage;
        score += damage;
        std::cout << "\n Correct! The enemy receive " << damage << " damage!" << std::endl;
    }
    else
    {
        int damage = 15;
        playerHP -= damage;
        std::cout << "\n Incorrect! You receive " << damage << " damage!" << std::endl;
    }
}

void Battle::showBattleStatus()
{
    std::cout << "\n=== Battle State ===" << std::endl;
    std::cout << "Your HP: " << playerHP << std::endl;
    std::cout << "Enemy HP: " << enemyHP << std::endl;
    std::cout << "Score: " << score << std::endl;
    std::cout << "========================" << std::endl;
}

void Battle::showResult()
{
    std::cout << "\n=== Batlle EnD ===" << std::endl;
    if (playerHP <= 0)
    {
        std::cout << "You loss!" << std::endl;
    }
    else if (enemyHP <= 0)
    {
        std::cout << "Victory! You defeated the enemy!" << std::endl;
    }
    std::cout << "Final Score: " << score << std::endl;
}

int Battle::getFinalScore() const
{
    return score;
}