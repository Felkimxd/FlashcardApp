#include <iostream>
#include <string>
#include <vector>
#include <flashcard.h>

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
    bool running = true;
    int option = 0;

    while (running)
    {
        switch (option = Menu())
        {
        case 1:
            /*code*/
            break;
        case 2:
            /* code */
            break;
        case 3:
            /* code */
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
