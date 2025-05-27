#ifndef FLASHCARD_H
#define FLASHCARD_H

#include <string>

class Flashcard{

    public:
        Flashcard(int id, const std::string &question, const std::string  &answer, float grade, int triesCounter, int estimatedTimeSeconds);

        std::string const getQuestion();
        std::string const getAnswer();
        int const getID();
        float const getGrade();
        int const gettriesCounter();
        int const getestimatedTIme();
        void gradeCalc(float const &timeTakeIt, float const &userFeedback);
        void IncrementTries();


    private:
        
        int id;
        std::string question;
        std::string answer;
        float grade;
        int triesCounter;
        int estimatedTimeSeconds;

        
};

#endif // FLASHCARD_H