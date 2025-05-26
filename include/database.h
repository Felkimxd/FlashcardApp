#include <string>
#include "sqlite3.h"
#include <vector>
#include <utility>

enum tables
{
    Flashcards = 1,
    Users = 2,
    Game = 3,
    Deck = 4,

};

struct FlashcardData
{
    std::string corrTable;
    std::string question;
    std::string answer;
    int triesCounter = 0;
    int estimatedTime = 0;
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

using FlashcarQA = std::vector<std::pair<std::string, std::string>>;
class dataBaseManager
{

public:
    dataBaseManager();

    sqlite3 *db;

    void insertRegister(tables tabletype, void *data);
    void readRegister(tables tableType, std::string const &ID = "", std::string const &deckName = "");
    void deleteRegister(tables tableType, std::string const &ID, std::string const &deckName = "");
    void editRegister(tables tableType, std::string const &ID, void *newData, const std::string &deckName = "");

    void createDeckTable(const std::string &deckName);
    bool checkDeckExists(const std::string &deckName);

    FlashcarQA retrieve_Flashcards(std::string &subject, int const &flashcardQuantity);

private:
    void createTables();

    const char *DBNAME = "C:\\CARPETAS IMPORTANTES\\Carpetas\\FlashcardApp\\archives\\data\\FlashcardApp.db";

    // const char *createDeckTableTemplate =
    //     "CREATE TABLE IF NOT EXISTS (?) ("
    //     "ID INTEGER PRIMARY KEY, "
    //     "Question TEXT NOT NULL, "
    //     "Answer TEXT NOT NULL, "
    //     "Grade INTEGER DEFAULT 0, "
    //     "TriesCounter INTEGER DEFAULT 0, "
    //     "EstimatedTime INTEGER DEFAULT 0"
    //     ");";

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

    const std::string insertFlashcardQueryTemplate =
        "INSERT INTO (?) (Question, Answer, Grade, TriesCounter, EstimatedTime) "
        "VALUES (?, ?, NULL, 0, ?);";

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