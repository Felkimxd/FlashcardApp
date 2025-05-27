#include <vector>
#include "flashcard.h"
#include "database.h"

class studySession{

    public:
        studySession(std::vector<Flashcard> flashcardvector,std::string const &deckName);
        std::vector<Flashcard> flashcards;
        std::vector<Flashcard> toanswerFlashcards;

    private:
        
        std::string deckName;
        
        void shuffleVector(std::vector<Flashcard> &vec1);

        float userFeedback();

        void studyLoop();
        void StudyController();
};