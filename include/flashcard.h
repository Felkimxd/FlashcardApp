#include <string>

class Flashcard{

    public:

        Flashcard(std::string question, std::string answer, float grade);

        void setQuestion(std::string const &question);
        void setAnswer(std::string const &answer);

        std::string const getQuestion();
        std::string const getAnswer();

    private:
        std::string question;
        std::string answer;
        float grade;
        int triesCounter;

};