#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "sqlite3.h"
#include <vector>
#include <utility>
#include "flashcard.h"

enum tables
{
    Flashcards = 1,
    Users = 2,
    Game = 3,
    Deck = 4,

};
struct FlashcardData
{
    std::string question;
    std::string answer;
    float grade;
    int triesCounter = 0;
    float estimatedTime = 0;
};

struct UserData
{
    std::string username;
    std::string password;
};

struct GameData
{
    std::string range;
};

struct DeckData
{
    std::string DeckN;
};

class dataBaseManager
{

public:
    dataBaseManager();

    sqlite3 *db;

    void insertRegister(tables tabletype, void *data, std::string const &deckName = "");
    void readRegister(tables tableType, std::string const &ID = "", std::string const &deckName = "");
    void deleteRegister(tables tableType, std::string const &ID, std::string const &deckName = "");
    void editRegister(tables tableType, std::string const &ID, void *newData, const std::string &deckName = "");

    bool getDeckName(const std::string &ID, std::string &deckName);
    void createDeckTable(const std::string &deckName);
    bool checkDeckExists(std::string const &ID);

    std::vector<Flashcard> retrieve_Flashcards(std::string &deckName);

private:
    void createTables();

    const char *DBNAME = "C:\\CARPETAS IMPORTANTES\\Carpetas\\FlashcardApp\\archives\\data\\FlashcardApp.db";

    const char *createUser =
        "CREATE TABLE IF NOT EXISTS User ("
        "ID INTEGER PRIMARY KEY, "
        "Username TEXT, "
        "Password TEXT"
        ");";

    const char *createGame =
        "CREATE TABLE IF NOT EXISTS Game ("
        "ID INTEGER PRIMARY KEY, "
        "Range TEXT);";

    const char *createDecks =
        "CREATE TABLE IF NOT EXISTS Decks ("
        "ID INTEGER PRIMARY KEY, "
        "Deck TEXT UNIQUE NOT NULL"
        ");";

    const std::string insertUsersQuery =
        "INSERT INTO Users (Username,Password) VALUES (?,?);";

    const std::string insertGameQuery =
        "INSERT INTO Game (Range) VALUES (?);";

    const std::string insertSubjectsQuery =
        "INSERT INTO Subjects (Subject) "
        "SELECT ? WHERE NOT EXISTS ("
        "SELECT 1 FROM Subjects WHERE Subject = ?"
        ");";
};

#endif // DATABASE_H