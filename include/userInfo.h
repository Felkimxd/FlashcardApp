#include "database.h"
#include <string>

const char *createUser =
    "CREATE TABLE IF NOT EXISTS User ("
    "ID INTEGER PRIMARY KEY, "
    "Username TEXT, "
    "Password TEXT"
    ");";

struct UserData {

    std::string user;
    std::string password;
    
};

class UserLogin : public dataBaseManager{

    public:
    UserLogin() : dataBaseManager(){}

    sqlite3 *dbUsers;

private:



};
