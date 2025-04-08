#include <string>

class Flashcard {
    public:
        Flashcard(const std::string &question, const std::string &answer);

        int getId() const;
        std::string getQuestion() const;
        std::string getAnswer() const;

        void setQuestion(const std::string &question);
        void setAnswer(const std::string &answer);

    private:

        int id;
        std::string question;
        std::string answer;
    
    };