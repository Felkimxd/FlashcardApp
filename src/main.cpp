#include <iostream>
#include <string>
#include <vector>
#include "flashcard.h"
#include "database.h"

int Menu(){

    int option = 0;
    std::cout << "======================== Flashcard App =======================" << std::endl;
    std::cout << "1. Add Flashcard" << std::endl;
    std::cout << "2. Show Flashcards" << std::endl;
    std::cout << "3. Delete Flashcard" << std::endl;
    std::cout << "4. Edit Flashcard" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "==============================================================" << "\n";
    std::cout << "Select an option: ";
    std::cin >> option;
    std::cout << "\n";

    return option;

}


int main(){
    
    FlashcardData flashcard;
    UserData user;
    GameData game;
    dataBaseManager db;

    std::string ID;

    bool running = true;
    int option = 0;

    while (running)
    {
        switch (option = Menu())
        {
        case 1:

            std::cout << "Enter the subject: " << "\n";
            std::cin.ignore(); // Limpia el buffer antes de getline
            std::getline(std::cin, flashcard.subject);

            std::cout << "Enter the question: " << "\n";
            std::getline(std::cin, flashcard.question);

            std::cout << "Enter the answer: " << "\n";
            std::getline(std::cin, flashcard.answer);

            std::cout<< "\n";

            db.insertRegister(tables::Flashcards, &flashcard);

            break;
        case 2:
            db.readRegister(tables::Flashcards,ID);

            break;
        case 3:
            std::cout << "Insert the ID to delete " << "\n";
            std::cin >> ID;
            std::cin.ignore();
            std::cout<< "\n";

            db.deleteRegister(tables::Flashcards, ID);
            break;
        case 4:
            std::cout << "Insert the ID to edit " << "\n";
            std::cin >> ID;

            std::cin.ignore(); // Limpia el buffer

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
