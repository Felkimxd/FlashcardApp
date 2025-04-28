#include <string>

class Flashcard{

    public:
        void setQuestion(std::string const &question);
        void setAnswer(std::string const &answer);

        Flashcard(std::string question, std::string answer, float grade);

    private:
        std::string question;
        std::string answer;
        float grade;

        float calculateGrade(bool const &answerGrade);

};