#include <string>
#include "sqlite3.h"
#include <vector>
#include <utility>

enum tables
{
    Flashcards = 1,
    Users = 2,
    Game = 3,
    Subject = 4,

};

struct FlashcardData
{
    std::string question;
    std::string answer;
    std::string subject;
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

struct SubjectData
{
    std::string subjectN;
};

using FlashcarQA = std::vector<std::pair<std::string, std::string>>;
class dataBaseManager
{

public:
    dataBaseManager();

    sqlite3 *db;

    void insertRegister(tables tabletype, void *data);
    void readRegister(tables tableType, std::string const &ID);
    void deleteRegister(tables tableType, std::string const &ID);
    void editRegister(tables tableType, std::string const &ID, void *newData);

    FlashcarQA retrieve_Flashcards(std::string &subject, int const &flashcardQuantity);

private:
    void createTables();

    const char *DBNAME = "C:\\CARPETAS IMPORTANTES\\Carpetas\\FlashcardApp\\archives\\data\\FlashcardApp.db";

    const char *createFlashcards =
        "CREATE TABLE IF NOT EXISTS Flashcards ("
        "ID INTEGER PRIMARY KEY, "
        "Subject TEXT, "
        "Question TEXT, "
        "Answer TEXT, "
        "Grade INTEGER"
        ");";

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

    const char *createSubject =
        "CREATE TABLE IF NOT EXISTS Subjects ("
        "ID INTEGER PRIMARY KEY, "
        "Subject TEXT"
        ");";

    const std::string insertFlashcardQuery =
        "INSERT INTO Flashcards (Question, Answer,Grade) VALUES (?, ?, NULL);";

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