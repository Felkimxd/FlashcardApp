#include <iostream>
#include <string>
#include <vector>
#include "flashcard.h"
#include "database.h"
#include <limits>


int Menu(){

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

int Menu_Decks()
{

    int option = 0;
    std::cout << "\n======================== Deck Options =======================" << std::endl;
    std::cout << "1. Add Flashcard" << std::endl;
    std::cout << "2. Show Flashcards" << std::endl;
    std::cout << "3. Delete Flashcard" << std::endl;
    std::cout << "4. Edit Flashcard" << std::endl;
    std::cout << "5. Exit" << std::endl;
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

    dataBaseManager db;

    std::string ID;
    std::string Deck;

    bool running1 = true;
    bool running2 = false;

    int option = 0;

    while (running1){

        DeckData deck;
        std::string deckName;

        switch (option = Menu())
        {
        case 1:{

            bool deckExists = false;                                                        
            
            db.readRegister(tables::Deck);

            std::cout << "Enter Deck Name " << "\n";
            std::getline(std::cin, deckName);

            deckExists = db.checkDeckExists(deckName);

            std::cout << deckExists << std ::endl;
            
            if (!deckExists){

                std::cout << "\nError: Deck '" << deckName << "' does not exist.";
                running1 = true;
            }
            else{

                running2 = true;
            }
            
            break;
        }

        case 2:
            db.readRegister(tables::Deck);

            std::cout << "Insert the ID to delete " << "\n";
            std::cin >> ID;
            std::cin.ignore();
            std::cout << "\n";

            db.deleteRegister(tables::Deck, ID);

            break;

        case 3:{

            std::string DeckName;

            std::cout << "Enter the Deck name " << "\n";
            std::getline(std::cin, DeckName);

            db.createDeckTable(DeckName);
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
            FlashcardData flashcard;
            UserData user;
            GameData game;
            DeckData deck;

            flashcard.corrTable = deckName;

            switch (option = Menu_Decks())
            {
            case 1:
            {
                std::cout << "Enter the question: ";
                std::getline(std::cin, flashcard.question);

                std::cout << "Enter the answer: ";
                std::getline(std::cin, flashcard.answer);

                std::cout << "Enter the estimated time (in seconds): ";
                std::string tempTime;
                std::getline(std::cin, tempTime);

                try
                {
                    flashcard.estimatedTime = std::stoi(tempTime);
                }
                catch (const std::invalid_argument &e)
                {
                    std::cout << "Error: Invalid number\n";
                    flashcard.estimatedTime = 0;
                }
                catch (const std::out_of_range &e)
                {
                    std::cout << "Error: Out of range value\n";
                    flashcard.estimatedTime = 0;
                }

                std::cout << "\n";
                db.insertRegister(tables::Flashcards, &flashcard);
                break;
            }
            case 2:
                db.readRegister(tables::Flashcards,"", deckName);
                break;
            case 3:
            {
                db.readRegister(tables::Flashcards,"", deckName);
                std::cout << "Insert the ID to delete\n";
                std::cin >> ID;
                std::cin.ignore();
                std::cout << "\n";
                db.deleteRegister(tables::Flashcards, ID,deckName);
                break;
            }
            case 4:
            {
                int parameters_option;
                db.readRegister(tables::Flashcards, "", deckName);
                std::cout << "Insert the ID to edit\n";
                std::cin >> ID;
                std::cin.ignore();

                parameters_option = Menu_Decks_Parameters();

                switch (parameters_option)
                {
                case 1:
                    std::cout << "Enter the question:\n";
                    std::getline(std::cin, flashcard.question);
                    break;
                case 2:
                    std::cout << "Enter the answer:\n";
                    std::getline(std::cin, flashcard.answer);
                    break;
                case 3:
                {
                    std::cout << "Enter the estimated time (seconds):\n";
                    std::string tempTime;
                    std::getline(std::cin, tempTime);
                    try
                    {
                        flashcard.estimatedTime = std::stoi(tempTime);
                    }
                    catch (const std::invalid_argument &e)
                    {
                        std::cout << "Error: Invalid number\n";
                        flashcard.estimatedTime = 0;
                    }
                    catch (const std::out_of_range &e)
                    {
                        std::cout << "Error: Out of range value\n";
                        flashcard.estimatedTime = 0;
                    }
                    break;
                }
                default:
                    break;
                }
                db.editRegister(tables::Flashcards, ID, &flashcard, deckName);
                break;
            }
            case 5:
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
