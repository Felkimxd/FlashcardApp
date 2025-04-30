#include <string>
#include <iostream>
#include <fstream>

class dataManager{

    public:
        std::string setStorage(std::string const &DIR);

    private:
        std::string storageDIR;
};