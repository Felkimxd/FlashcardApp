#include <string>

class Flashcard{

    public:

        Flashcard(std::string question, std::string answer);

        void setQuestion(std::string const &question);
        void setAnswer(std::string const &answer);
        void setTime(int const &stimatedTime);

        std::string const getQuestion();
        std::string const getAnswer();

    private:
        std::string question;
        std::string answer;

        float grade;
        int triesCounter;
        int stimatedTimeSeconds;

        void gradeCalc();
        void addCounter();
};