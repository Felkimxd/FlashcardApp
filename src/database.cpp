#include "sqlite3.h"
#include "database.h"
#include <iostream>

dataBaseManager::dataBaseManager(){
    createTables();
}

void dataBaseManager::createTables(){

    sqlite3_open(this->DBNAME, &this->db);

    char *errorMsg = nullptr;

    sqlite3_exec(this->db, this->createUser , nullptr, nullptr, &errorMsg);
    sqlite3_exec(this->db, this->createGame , nullptr, nullptr, &errorMsg);
    sqlite3_exec(this->db, this->createDecks , nullptr, nullptr, &errorMsg);

    sqlite3_close(this->db);

}

bool dataBaseManager::checkDeckExists(const std::string &deckName)
{
    sqlite3_stmt *stmt = nullptr;
    std::string query = "SELECT 1 FROM Decks WHERE Deck = ?;";
    bool exists = false;

    sqlite3_open(this->DBNAME, &this->db);

    if (sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, deckName.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            exists = true;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(this->db);
    return exists;
}

void dataBaseManager::createDeckTable(const std::string &deckName)
{
    
    sqlite3_stmt *stmt = nullptr;
    std::string checkQuery = "SELECT 1 FROM Decks WHERE Deck = ?;";
    bool success = false;
    char *errorMsg = nullptr;

    sqlite3_open(this->DBNAME, &this->db);

    if (sqlite3_prepare_v2(this->db, checkQuery.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, deckName.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_ROW)
        {

            std::string createTableQuery = 
            "CREATE TABLE IF NOT EXISTS '" + deckName + "' ("
            "ID INTEGER PRIMARY KEY, "
            "Question TEXT NOT NULL, "
            "Answer TEXT NOT NULL, "
            "Grade INTEGER DEFAULT 0, "
            "TriesCounter INTEGER DEFAULT 0, "
            "EstimatedTime INTEGER DEFAULT 0"
            ");";

    
            if (sqlite3_exec(this->db, createTableQuery.c_str(), nullptr, nullptr, &errorMsg) == SQLITE_OK)
            {
                std::string insertQuery = "INSERT INTO Decks (Deck) VALUES (?);";
                sqlite3_stmt *insertStmt;

                if (sqlite3_prepare_v2(this->db, insertQuery.c_str(), -1, &insertStmt, nullptr) == SQLITE_OK)
                {
                    sqlite3_bind_text(insertStmt, 1, deckName.c_str(), -1, SQLITE_STATIC);
                    
                    if (sqlite3_step(insertStmt) == SQLITE_DONE) {
                        std::cout << "Deck '" << deckName << "' created successfully!" << std::endl;
                        success = true;
                    }
                    sqlite3_finalize(insertStmt);
                }
            }
            else {
                std::cout << "Error creating deck table: " << errorMsg << std::endl;
                sqlite3_free(errorMsg);
            }
        }
        else {
            std::cout << "Error: Deck '" << deckName << "' already exists!" << std::endl;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(this->db);
}

void dataBaseManager::insertRegister(tables tableType, void *data, const std::string &deckName)
{

    sqlite3_stmt *stmt = nullptr;
    std::string query ;
    int rc;
    sqlite3_open(this->DBNAME, &this->db);

    switch (tableType)
    {
    case Flashcards:{

        FlashcardData *flashcard = static_cast<FlashcardData *>(data);

        std::string insertFlashcardQueryTemplate =
        "INSERT INTO '"+ deckName +"' (Question, Answer, Grade, TriesCounter, EstimatedTime) "
        "VALUES (?, ?, NULL, 0, ?);";
        

        query = insertFlashcardQueryTemplate;

        sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, nullptr);

        sqlite3_bind_text(stmt, 1, flashcard->question.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, flashcard->answer.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, flashcard->estimatedTime);

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

    case Deck: {

        DeckData *deck = static_cast<DeckData *>(data);

        // Verify if the subject exits
        std::string checkQuery = "SELECT Subject FROM Decks WHERE Decks = ?;";
        sqlite3_stmt *checkStmt = nullptr;

        rc = sqlite3_prepare_v2(this->db, checkQuery.c_str(), -1, &checkStmt, nullptr);
        sqlite3_bind_text(checkStmt, 1, deck->DeckN.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(checkStmt) == SQLITE_ROW)
        {
            std::cout << "Deck '" << deck->DeckN << "' already exists!" << std::endl;
            sqlite3_finalize(checkStmt);
            break;
        }

        sqlite3_finalize(checkStmt);
    
        // If not exists proceed with the insertion
        query = this->insertSubjectsQuery;
        sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, nullptr);
        
        sqlite3_bind_text(stmt, 1, deck->DeckN.c_str(), -1, SQLITE_STATIC);

        std::cout << "Subject '" << deck->DeckN << "' registered succesfully!" << std::endl;

        
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

void dataBaseManager::readRegister(tables tableType, std::string const &ID, std::string const &deckName) 
{
    sqlite3_stmt *stmt = nullptr;
    std::string query;
    sqlite3_open(this->DBNAME, &this->db);
    int rc;

    switch (tableType)
    {
    case Flashcards:
    {
        if (!deckName.empty()) {
            // Si se proporciona un nombre de deck, mostrar las flashcards de ese deck
            query = "SELECT * FROM '" + deckName + "';";
        } else {
            // Si no se proporciona deck, mostrar mensaje de error
            std::cout << "Error: Specify the deck.\n";
            return;
        }

        rc = sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, nullptr);
        
        if (rc != SQLITE_OK) {
            std::cout << "Error to access the deck: " << sqlite3_errmsg(db) << std::endl;
            return;
        }

        std::cout << "\n=== Flashcards in '" << deckName << "' ===\n" << std::endl;
        
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            std::cout << "Flashcard ID: " << sqlite3_column_text(stmt, 0) << std::endl;
            std::cout << "Question: " << sqlite3_column_text(stmt, 1) << std::endl;
            std::cout << "Answer: " << sqlite3_column_text(stmt, 2) << std::endl;
            std::cout << "Grade: " << sqlite3_column_int(stmt, 3) << std::endl;
            std::cout << "Tries: " << sqlite3_column_int(stmt, 4) << std::endl;
            std::cout << "Estimated Time: " << sqlite3_column_int(stmt, 5) << std::endl;
            std::cout << "\n";
        }
        std::cout << "==========================================\n";
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

    case Deck:
    {
        query = "SELECT * FROM Decks;";

        sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, nullptr);

        std::cout << "\n=== Decks List ===\n"                                                                                                    << std::endl;

        while (sqlite3_step(stmt) == SQLITE_ROW)
        {

            std::cout << "ID: " << sqlite3_column_text(stmt, 0)
                      << " | Deck: " << sqlite3_column_text(stmt, 1) << std::endl;

        }
        std::cout << "\n===================" << std::endl;
        break;
    }

    default:
        std::cerr << "Table does not exist!" << std::endl;
        return;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(this->db);
}

bool dataBaseManager::getDeckName(const std::string &ID, std::string &deckName)
{
    sqlite3_stmt *stmt = nullptr;
    std::string query = "SELECT Deck FROM Decks WHERE ID = ?;";
    bool exists = false;

    sqlite3_open(this->DBNAME, &this->db);

    if (sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, ID.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            deckName = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
            exists = true;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(this->db);

    return exists;
}

void dataBaseManager::editRegister(tables tableType, const std::string &ID, void *newData, const std::string &deckName)
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
    

        if (!flashcard->question.empty()) {
            query = "UPDATE '"+ deckName +"' SET Question = ? WHERE ID = ?;";
        }
        else if (!flashcard->answer.empty()) {
            query = "UPDATE '" + deckName + "' SET Answer = ? WHERE ID = ?;";
        }
        else if (flashcard->estimatedTime != 0)
        {
            query = "UPDATE '"+ deckName +"' SET EstimatedTime = ? WHERE ID = ?;";
        }

        rc = sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, nullptr);

        std::cout << rc << std::endl;

        if (!flashcard->question.empty()) {
            sqlite3_bind_text(stmt, 1, flashcard->question.c_str(), -1, SQLITE_STATIC);
        }
        else if (!flashcard->answer.empty()) {
            sqlite3_bind_text(stmt, 1, flashcard->answer.c_str(), -1, SQLITE_STATIC);
        }
        else if (flashcard->estimatedTime != 0) {
            sqlite3_bind_int(stmt, 1, flashcard->estimatedTime);
        }
    
        sqlite3_bind_text(stmt, 2, ID.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            std::cout << "Flashcard updated successfully in deck '" << deckName << "'!" << std::endl;
        }
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

void dataBaseManager::deleteRegister(tables tableType, const std::string &ID, std::string const &deckName)
{
    sqlite3_stmt *stmt = nullptr;
    std::string query;
    sqlite3_open(this->DBNAME, &this->db);
    int rc;

    switch (tableType)
    {
    case Flashcards:
    {
        if (!deckName.empty())
        {
            // Si se proporciona un nombre de deck, borrar de esa tabla específica
            query = "DELETE FROM '" + deckName + "' WHERE ID = ?;";
        }
        else
        {
            std::cout << "Error: Specify the deck.\n";
            return;
        }

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            std::cout << "Flashcard deleted successfully from deck '" << deckName << "'!" << std::endl;
        }

        rc = sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, nullptr);

        if (rc != SQLITE_OK)
        {
            std::cout << "Error to acces the deck: " << sqlite3_errmsg(db) << std::endl;
            return;
        }

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
    
    case Deck:
    {
        // Primero obtener el nombre del deck usando el ID
        std::string getDeckQuery = "SELECT Deck FROM Decks WHERE ID = ?;";
        sqlite3_stmt *getDeckStmt = nullptr;
        std::string deckToDelete;

        // Asegurarnos de que no hay transacciones pendientes
        sqlite3_exec(this->db, "COMMIT", nullptr, nullptr, nullptr);

        if (sqlite3_prepare_v2(this->db, getDeckQuery.c_str(), -1, &getDeckStmt, nullptr) == SQLITE_OK)
        {
            sqlite3_bind_text(getDeckStmt, 1, ID.c_str(), -1, SQLITE_STATIC);

            if (sqlite3_step(getDeckStmt) == SQLITE_ROW)
            {
                deckToDelete = reinterpret_cast<const char *>(sqlite3_column_text(getDeckStmt, 0));

                // Finalizar la primera consulta antes de continuar
                sqlite3_finalize(getDeckStmt);

                // Borrar la tabla del deck
                std::string dropTableQuery = "DROP TABLE IF EXISTS '" + deckToDelete + "';";
                char *errorMsg = nullptr;

                // Cerrar y reabrir la conexión para asegurar que no hay bloqueos
                sqlite3_close(this->db);
                sqlite3_open(this->DBNAME, &this->db);

                if (sqlite3_exec(this->db, dropTableQuery.c_str(), nullptr, nullptr, &errorMsg) == SQLITE_OK)
                {
                    // Borrar el registro del deck
                    query = "DELETE FROM Decks WHERE ID = ?;";

                    if (sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
                    {
                        sqlite3_bind_text(stmt, 1, ID.c_str(), -1, SQLITE_STATIC);

                        if (sqlite3_step(stmt) == SQLITE_DONE)
                        {
                            std::cout << "Deck '" << deckToDelete << "' erased succesfully!" << std::endl;
                        }
                    }
                }
                else
                {
                    std::cout << "Error at the moment of erase the table: " << errorMsg << std::endl;
                    sqlite3_free(errorMsg);
                }
            }
        }

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            std::cout << "Deck '" << deckToDelete << "' and all its flashcards deleted successfully!" << std::endl;
        }

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

std::vector<Flashcard> dataBaseManager::retrieve_Flashcards(std::string &deckName)
{
    std::vector<Flashcard> flashcards;
    sqlite3_stmt *stmt = nullptr;
    std::string query;

    if (sqlite3_open(this->DBNAME, &this->db) != SQLITE_OK)
    {
        sqlite3_close(this->db);
        return flashcards; 
    }

    query = "SELECT * FROM \"" + deckName + "\";"; 

    int rc = sqlite3_prepare_v2(this->db, query.c_str(), -1, &stmt, nullptr);
    if (rc == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            
            const char *questionText = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
            const char *answerText = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));

            std::string question = questionText ? std::string(questionText) : "";
            std::string answer = answerText ? std::string(answerText) : "";

            Flashcard card(
                sqlite3_column_int(stmt, 0),    // ID
                question,                       // Question
                answer,                         // Answer
                sqlite3_column_double(stmt, 3), // Grade
                sqlite3_column_int(stmt, 4),    // TriesCounter
                sqlite3_column_int(stmt, 5)     // EstimatedTime
            );

            flashcards.push_back(std::move(card));
        }
        sqlite3_finalize(stmt);
    }
    else
    {
        if (stmt)
        {
            sqlite3_finalize(stmt);
        }
    }

    sqlite3_close(this->db);
    return flashcards;
}