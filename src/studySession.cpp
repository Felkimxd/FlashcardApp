#include "studySession.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
#include <string>

void pauseConsole(std::string message)
{
    std::cout << "\n"+message;
    std::cin.get();
}

void Screenclean()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

studySession::studySession(std::vector<Flashcard> flashcardvector, std::string const &deckName)
{

    this->flashcards = flashcardvector;
    this->deckName = deckName;
    this->toanswerFlashcards = flashcardvector;
    studyLoop();

}
void studySession::StudyController(){

    std::cout << "Question: " << toanswerFlashcards[0].getQuestion() << std::endl;

    // Init time
    auto startTime = std::chrono::high_resolution_clock::now();

    pauseConsole("Press enter to show the answer...");

    // End time
    auto endTime = std::chrono::high_resolution_clock::now();
   
    // Time in seconds
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
    
    float timeSpent = duration.count();
    

    for (Flashcard &card: flashcards){
        if (toanswerFlashcards[0].getID() == card.getID()){

            std::cout << "Answer: " << toanswerFlashcards[0].getAnswer() << std::endl;
            std::cout << "\nTime that takes solve it: " << timeSpent << std::endl;
            pauseConsole("Comprobe your Answer!");

            card.gradeCalc(timeSpent, userFeedback());

            card.IncrementTries();

            if (card.getGrade() >= 5)
            {
                toanswerFlashcards.erase(toanswerFlashcards.begin());
            }
            std::cout << "TriesF: " << card.gettriesCounter() << std::endl;
            break;
        }
        
    }

    pauseConsole("Press enter to continue to the next question... ");
}

float studySession::userFeedback(){

    float feedbackGrade;

    int option = 0;
    std::cout << "\n======================== Satisfacction about Question =======================" << std::endl;
    std::cout << "1. Easy" << std::endl;
    std::cout << "2. Medium" << std::endl;
    std::cout << "3. Hard" << std::endl;
    std::cout << "===============================================================" << "\n";
    std::cout << "Select an option: ";
    std::cin >> option;
    std::cin.ignore();
    std::cout << "\n";
    

    switch (option)
    {
    case 1:
        feedbackGrade = 1;
        break;
    case 2:
        feedbackGrade = 0.5;
        break;
    case 3:
        feedbackGrade = 0;
        break;
    
    default:
        break;
    }

    return feedbackGrade;
}


void studySession::studyLoop(){
    
    while (!toanswerFlashcards.empty())
    {
        shuffleVector(toanswerFlashcards);
        Screenclean();
        std::cout << "\n======================== DECK " + deckName + " STUDY SESSION =======================\n"<< std::endl;
        StudyController();

    }
    pauseConsole("Congratulations you finished a study session! :D, press Enter to continue...");
}

void studySession::shuffleVector(std::vector<Flashcard> &vec1)
{
    // Use the same seed with to shuffle
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    std::shuffle(vec1.begin(), vec1.end(), generator);
}