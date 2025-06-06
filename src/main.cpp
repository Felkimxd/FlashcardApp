#include <iostream>
#include <string>
#include <vector>
#include "database.h"
#include <limits>
#include "flashcard.h"
#include "studySession.h"
#include "gamification.h"
#include <windows.h>

#include <chrono>
#include <thread>

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


void pauseConsole(int seconds = 2)
{
    std::cout << "\nPress enter to continue...";
    std::cin.get();
    clearScreen();
}

int Menu()
{
    clearScreen();
    int option = 0;
    std::cout << "\n======================== Flashcard App =======================" << std::endl;
    std::cout << "1. Select Deck" << std::endl;
    std::cout << "2. Delete Deck" << std::endl;
    std::cout << "3. Create Deck" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "===============================================================" << "\n";
    std::cout << "Select an option: ";
    std::cin >> option;
    std::cin.ignore();
    std::cout << "\n";

    return option;
}

int Menu_Decks(const std::string &activeDeck)
{
    clearScreen();
    int option = 0;
    std::cout << "\n======================== Deck Options =======================" << std::endl;
    std::cout << "Active Deck: " << activeDeck << std::endl;
    std::cout << "1. BEGIN A STUDY SESSION" << std::endl;
    std::cout << "2. BATTLE MODE" << std::endl;
    std::cout << "3. Add Flashcard" << std::endl;
    std::cout << "4. Show Flashcards" << std::endl;
    std::cout << "5. Delete Flashcard" << std::endl;
    std::cout << "6. Edit Flashcard" << std::endl;
    std::cout << "7. Exit" << std::endl;
    std::cout << "==============================================================" << "\n";
    std::cout << "Select an option: ";
    std::cin >> option;
    std::cin.ignore();
    std::cout << "\n";

    return option;
}

int Menu_Decks_Parameters()
{

    int option = 0;
    std::cout << "\n======================== Flashcard Parameters =======================" << std::endl;
    std::cout << "1. Question" << std::endl;
    std::cout << "2. Answer" << std::endl;
    std::cout << "3. Estimated time" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "==============================================================" << "\n";
    std::cout << "Select an option: ";
    std::cin >> option;
    std::cin.ignore();
    std::cout << "\n";

    return option;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    std::setlocale(LC_ALL, "es_ES.UTF-8");
    dataBaseManager db;

    std::string ID;
    std::string Deck;

    bool running1 = true;
    bool running2 = false;

    int option = 0;

    while (running1)
    {

        DeckData deck;
        std::string deckName;

        switch (option = Menu())
        {
        case 1:
        {

            bool deckExists = false;
            std::string selectedDeckName;

            db.readRegister(tables::Deck);

            std::cout << "Enter Deck ID: ";
            std::getline(std::cin, ID);

            if (db.getDeckName(ID, selectedDeckName))
            {
                deckName = selectedDeckName;
                running1 = true;
                running2 = true;
                std::cout << "\nDeck '" << deckName << "' selected successfully!" << std::endl;
            }
            else
            {
                running1 = true;
                running2 = false;
                std::cout << "\nError: Deck with ID '" << ID << "' does not exist.\n";
            }

            pauseConsole();
            break;
        }

        case 2:
            db.readRegister(tables::Deck);

            std::cout << "Insert the ID to delete " << "\n";
            std::cin >> ID;
            std::cin.ignore();
            std::cout << "\n";

            db.deleteRegister(tables::Deck, ID);
            pauseConsole();
            break;

        case 3:
        {

            std::string DeckName;

            std::cout << "Enter the Deck name " << "\n";
            std::getline(std::cin, DeckName);

            db.createDeckTable(DeckName);
            pauseConsole();
            break;
        }
        case 4:

            std::cout << "Exiting..." << std::endl;
            running1 = false;
            running2 = false;
            break;

        default:
            break;
        }

        while (running2)
        {
            FlashcardData flashcardData;
            GameData game;
            DeckData deck;

            switch (option = Menu_Decks(deckName))
            {
            case 1: 
            {

                clearScreen();
                std::vector<Flashcard> flashcardVector = db.retrieve_Flashcards(deckName);

                studySession Session(flashcardVector, deckName);
        
                for (Flashcard &card : Session.flashcards){
                    

                    flashcardData.grade = card.getGrade();
                    flashcardData.triesCounter = card.gettriesCounter();
                    
                    db.editRegister(tables::Flashcards, std::to_string(card.getID()), &flashcardData, deckName);
                }
                pauseConsole();
                break;
            }
            case 2:
            {
                GameData game;

                clearScreen();
                std::vector<Flashcard> flashcardVector = db.retrieve_Flashcards(deckName);

                if (flashcardVector.empty())
                {
                    std::cout << "You need flashcards to begin the battle!" << std::endl;
                    pauseConsole();
                    break;
                }

                Battle battle(flashcardVector, deckName);
                battle.startBattle();

                // Actualizar puntos del usuario
                int battleScore = battle.getFinalScore();
                db.insertRegister(tables::Game, &game, deckName);

                pauseConsole();
                break;
            }
            case 3:
            {
                std::cout << "Enter the question: ";
                std::getline(std::cin, flashcardData.question);

                std::cout << "Enter the answer: ";
                std::getline(std::cin, flashcardData.answer);

                std::cout << "Enter the estimated time (in seconds): ";
                std::string tempTime;
                std::getline(std::cin, tempTime);

                try
                {
                    flashcardData.estimatedTime = std::stoi(tempTime);
                }
                catch (const std::invalid_argument &e)
                {
                    std::cout << "Error: Invalid number\n";
                    flashcardData.estimatedTime = 0;
                }
                catch (const std::out_of_range &e)
                {
                    std::cout << "Error: Out of range value\n";
                    flashcardData.estimatedTime = 0;
                }

                std::cout << "\n";
                db.insertRegister(tables::Flashcards, &flashcardData, deckName);
                std::cout << "\nFlashcard added successfully to deck '" << deckName << "'!" << std::endl;
                pauseConsole();
                break;
            }
            case 4:
                std::cout << "\nShowing flashcards from deck '" << deckName << "':" << std::endl;
                db.readRegister(tables::Flashcards, "", deckName);
                pauseConsole();
                break;
            case 5:
            {
                db.readRegister(tables::Flashcards, "", deckName);
                std::cout << "Insert the ID to delete from deck: \n";
                std::cin >> ID;
                std::cin.ignore();
                std::cout << "\n";
                db.deleteRegister(tables::Flashcards, ID, deckName);
                pauseConsole();
                break;
            }
            case 6:
            {
                int parameters_option;
                db.readRegister(tables::Flashcards, "", deckName);
                std::cout << "Insert the ID to edit from deck: \n";
                std::cin >> ID;
                std::cin.ignore();

                parameters_option = Menu_Decks_Parameters();

                switch (parameters_option)
                {
                case 1:
                    std::cout << "Enter the question:\n";
                    std::getline(std::cin, flashcardData.question);
                    break;
                case 2:
                    std::cout << "Enter the answer:\n";
                    std::getline(std::cin, flashcardData.answer);
                    break;
                case 3:
                {
                    std::cout << "Enter the estimated time (seconds):\n";
                    std::string tempTime;
                    std::getline(std::cin, tempTime);
                    try
                    {
                        flashcardData.estimatedTime = std::stoi(tempTime);
                    }
                    catch (const std::invalid_argument &e)
                    {
                        std::cout << "Error: Invalid number\n";
                        flashcardData.estimatedTime = 0;
                    }
                    catch (const std::out_of_range &e)
                    {
                        std::cout << "Error: Out of range value\n";
                        flashcardData.estimatedTime = 0;
                    }
                    break;
                }
                default:
                    break;
                }
                db.editRegister(tables::Flashcards, ID, &flashcardData, deckName);
                break;
            }
            case 7:
                std::cout << "Exiting..." << std::endl;
                running2 = false;
                break;
            default:
                std::cout << "Invalid option. Please try again.\n\n";
                break;
            }
        }
    }
    return 0;
}
