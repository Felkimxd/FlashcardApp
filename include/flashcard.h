#include <string>

class Flashcard{

    public:

        Flashcard(std::string question, std::string answer);

        void updateEstimatedTime(int const &estimatedTime);
        void setQuestion(std::string const &question);
        void setAnswer(std::string const &answer);
        

        std::string const getQuestion();
        std::string const getAnswer();
        std::string const getID();
        std::string const getGrade();
        std::string const gettriesCounter();
        std::string const getestimatedTIme();

    private:
        void gradeCalc(float const &timeTakeIt, float const &userFeedback);
        void IncrementTries();

        int id;
        std::string question;
        std::string answer;
        float grade;
        int triesCounter;
        int estimatedTimeSeconds;

        
};