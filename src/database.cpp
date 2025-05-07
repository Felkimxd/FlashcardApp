#include "sqlite3.h"
#include "database.h"
#include <iostream>

dataBaseManager::dataBaseManager(){
    createTables();
}

void dataBaseManager::createTables(){

    sqlite3_open(this->DBNAME, &this->db);

    char *errorMsg = nullptr;

    sqlite3_exec(this->db , this->createFlashcards, nullptr, nullptr, &errorMsg);
    sqlite3_exec(this->db, this->createUser , nullptr, nullptr, &errorMsg);
    int result = sqlite3_exec(this->db, this->createGame , nullptr, nullptr, &errorMsg);
    
    sqlite3_close(this->db);

}

void dataBaseManager::insertRegister(tables tableType, void *data)
{

    sqlite3_stmt *stmt = nullptr;
    std::string query ;
    int rc;
    sqlite3_open(this->DBNAME, &this->db);

    switch (tableType)
    {
    case Flashcards:{

        FlashcardData *flashcard = static_cast<FlashcardData *>(data);
        query = this->insertFlashcardQuery;

        sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, nullptr);

        sqlite3_bind_text(stmt, 1, flashcard->question.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, flashcard->answer.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, flashcard->subject.c_str(), -1, SQLITE_STATIC);

        break;
    }
        
    case Users:{
        UserData *user = static_cast<UserData *>(data);
        query = this->insertUsersQuery;
        sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, nullptr);

        sqlite3_bind_text(stmt, 1, user->username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, user->password.c_str(), -1, SQLITE_STATIC);

        break;
    }
    case Game:{

        GameData* game = static_cast<GameData*>(data);
        query = this->insertGameQuery;
        sqlite3_bind_text(stmt, 1, game->range.c_str(), -1, SQLITE_STATIC);

        break;
    }
    
    default:{
        std::cerr << "Table does not exist!" << std::endl;
        break;
    }
    };
    
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(this->db);

    
}

void dataBaseManager::readRegister(tables tableType, std::string const &ID) 
{
    sqlite3_stmt *stmt = nullptr;
    std::string query;
    sqlite3_open(this->DBNAME, &this->db);
    int rc;

    switch (tableType)
    {
    case Flashcards:
    {
        query = "SELECT * FROM Flashcards;";
        sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, nullptr);
        
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            std::cout << "Flashcard ID: " << sqlite3_column_text(stmt, 0) << std::endl;
            std::cout << "Subject: " << sqlite3_column_text(stmt, 1) << std::endl;
            std::cout << "Question: " << sqlite3_column_text(stmt, 2) << std::endl;
            std::cout << "Answer: " << sqlite3_column_text(stmt, 3) << std::endl;
            std::cout << "Grade: " << sqlite3_column_int(stmt, 4) << std::endl;
            std::cout << "\n";
        }
        break;
    }

    case Users:
    {
        query = "SELECT * FROM User WHERE ID = ?;";
        sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, nullptr);

        sqlite3_bind_text(stmt, 1, ID.c_str(), -1, SQLITE_STATIC);

        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            std::cout << "User ID: " << sqlite3_column_text(stmt, 0) << std::endl;
            std::cout << "Username: " << sqlite3_column_text(stmt, 1) << std::endl;
            std::cout << "Password: " << sqlite3_column_text(stmt, 2) << std::endl;
        }
        break;
    }

    case Game:
    {
        query = "SELECT * FROM Game WHERE ID = ?;";
        sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, nullptr);
        
        sqlite3_bind_text(stmt, 1, ID.c_str(), -1, SQLITE_STATIC);

        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            std::cout << "Game ID: " << sqlite3_column_text(stmt, 0) << std::endl;
            std::cout << "Range: " << sqlite3_column_text(stmt, 1) << std::endl;
        }
        break;
    }

    default:
        std::cerr << "Table does not exist!" << std::endl;
        return;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(this->db);
}

void dataBaseManager::editRegister(tables tableType, const std::string &ID, void *newData)
{
    sqlite3_stmt *stmt = nullptr;
    std::string query;
    int rc;
 
    sqlite3_open(this->DBNAME, &this->db);
    
    switch (tableType)
    {
    case Flashcards:
    {
        FlashcardData *flashcard = static_cast<FlashcardData *>(newData);
        query = "UPDATE Flashcards SET Subject = ?, Question = ?, Answer = ? WHERE ID = ?;";

        rc = sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, nullptr);

        sqlite3_bind_text(stmt, 1, flashcard->subject.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, flashcard->question.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, flashcard->answer.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, ID.c_str(), -1, SQLITE_STATIC);
        break;
    }

    case Users:
    {
        UserData *user = static_cast<UserData *>(newData);
        query = "UPDATE User SET Username = ?, Password = ? WHERE ID = ?;";

        sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, nullptr);

        sqlite3_bind_text(stmt, 1, user->username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, user->password.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, ID.c_str(), -1, SQLITE_STATIC);
        break;
    }

    case Game:
    {
        GameData *game = static_cast<GameData *>(newData);
        query = "UPDATE Game SET Range = ? WHERE ID = ?;";

        sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, nullptr);

        sqlite3_bind_text(stmt, 1, game->range.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, ID.c_str(), -1, SQLITE_STATIC);
        break;
    }

    default:{
        std::cerr << "Table Does not Exist!" << std::endl;
        break;
    }

    }

    sqlite3_step(stmt);

    sqlite3_finalize(stmt);
    sqlite3_close(this->db);
}

void dataBaseManager::deleteRegister(tables tableType, const std::string &ID)
{
    sqlite3_stmt *stmt = nullptr;
    std::string query;
    sqlite3_open(this->DBNAME, &this->db);

    switch (tableType)
    {
    case Flashcards:
    {
        query = "DELETE FROM Flashcards WHERE ID = ?;";

        sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, nullptr);
        sqlite3_bind_text(stmt, 1, ID.c_str(), -1, SQLITE_STATIC);
        break;
    }

    case Users:
    {
        query = "DELETE FROM User WHERE ID = ?;";

        sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, nullptr);
        sqlite3_bind_text(stmt, 1, ID.c_str(), -1, SQLITE_STATIC);
        break;
    }

    case Game:
    {
        query = "DELETE FROM Game WHERE ID = ?;";

        sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, nullptr);
        sqlite3_bind_text(stmt, 1, ID.c_str(), -1, SQLITE_STATIC);
        break;
    }

    default:
        std::cerr << "Table does not exist!" << std::endl;
        return;
    }

    sqlite3_step(stmt);

    sqlite3_finalize(stmt);
    sqlite3_close(this->db);
}