#include <iostream>
#include <string>
#include <vector>
#include "flashcard.h"
#include "database.h"
#include <limits>

int Menu(){
    
    int option = 0;
    std::cout << "\n======================== Flashcard App =======================" << std::endl;
    std::cout << "1. Add Flashcard" << std::endl;
    std::cout << "2. Show Flashcards" << std::endl;
    std::cout << "3. Delete Flashcard" << std::endl;
    std::cout << "4. Edit Flashcard" << std::endl;
    std::cout << "5. Register a Subject" << std::endl;
    std::cout << "6. Show Subjects" << std::endl;
    std::cout << "7. Exit" << std::endl;
    std::cout << "==============================================================" << "\n";
    std::cout << "Select an option: ";
    std::cin >> option;
    std::cin.ignore();
    std::cout << "\n";

    return option;

}


int main(){
    
    FlashcardData flashcard;
    UserData user;
    GameData game;
    SubjectData subject;

    dataBaseManager db;

    std::string ID;

    bool running = true;
    int option = 0;

    while (running)
    {
        switch (option = Menu())
        {
        case 1:{

            bool subjectExists = false;

            
            db.readRegister(tables::Subject);

            std::cout << "Enter the subject: ";
            std::getline(std::cin, flashcard.subject);
            
            subjectExists = db.checkSubjectExists(flashcard.subject);
            

            if (!subjectExists)
            {
                char option;
                std::cout << "\nError: Subject '" << flashcard.subject << "' does not exist.";
                continue;
            }
        

            else
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
            }

            break;
        }
        case 2:
            db.readRegister(tables::Flashcards,ID);

            break;
        
        case 3:

            db.readRegister(tables::Flashcards);
            
            std::cout << "Insert the ID to delete " << "\n";
            std::cin >> ID;
            std::cin.ignore();
            std::cout<< "\n";

            db.deleteRegister(tables::Flashcards, ID);
            break;
        
        case 4:
            std::cout << "Insert the ID to edit " << "\n";
            std::cin >> ID;

            std::cin.ignore();

            std::cout << "Enter the subject: " << "\n";
            std::getline(std::cin, flashcard.subject);

            std::cout << "Enter the question: " << "\n";
            std::getline(std::cin, flashcard.question);

            std::cout << "Enter the answer: " << "\n";
            std::getline(std::cin, flashcard.answer);
            
            std::cout<< "\n";

            db.editRegister(tables::Flashcards, ID, &flashcard);
            break;
        
        case 5:

            db.readRegister(tables::Subject);
            std::cin.ignore(); // Limpia el buffer
            std::cout << "Enter the subject: ";
            std::getline(std::cin, subject.subjectN);
            db.insertRegister(tables::Subject, &subject);
            break;
        
        case 6:

            db.readRegister(tables::Subject);
            break;
        
        case 7:

            std::cout << "Exiting..." << std::endl;
            running = false;
            break;
        

        default:
            std::cout << "Invalid option. Please try again." << std::endl;
            std::cout << '\n';

            break;
        
    }
    }
    return 0;
}
