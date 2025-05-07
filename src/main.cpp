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
    std::cout << "4. Exit" << std::endl;
    std::cout << "==============================================================" << "\n";
    std::cout << "Select an option: ";
    std::cin >> option;

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
            std::cin >> flashcard.subject;
            std::cout << "Enter the question: " << "\n";
            std::cin >> flashcard.question;
            std::cout << "Enter the answer: " << "\n";
            std::cin >> flashcard.answer;
            db.insertRegister(tables::Flashcards, &flashcard);

            break;
        case 2:
            std::cout << "Insert the ID to read: " << "\n";
            std::cin >> ID;
            db.readRegister(tables::Flashcards,ID);

            break;
        case 3:
            std::cout << "Insert the ID to delete " << "\n";
            std::cin >> ID;
            db.deleteRegister(tables::Flashcards, ID);
            break;
        case 4:
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
